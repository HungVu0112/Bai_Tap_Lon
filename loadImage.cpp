#include "loadImage.h"

BackGround::BackGround() {
	texture = NULL;
	width = 0;
	height = 0;
}

BackGround::~BackGround() {
	free();
}

bool BackGround::loadFromFile(string path) {
	free();

	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Could not load image ! " << IMG_GetError();
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
		newtexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newtexture == NULL) {
			cout << "Could not create texture ! " << SDL_GetError();
		}
		else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture = newtexture;
	return texture != NULL;
}

bool BackGround::loadFromText(string text, string textFont, SDL_Color textColor, int size) {
	free();

	font = TTF_OpenFont(textFont.c_str(), size);
	if (font == NULL) {
		cout << "Could not load Font ! " << endl;
		return false;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface == NULL) {
		cout << "Could not create text surface ! " << TTF_GetError();
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL) {
			cout << "Could not create texture ! " << SDL_GetError();
		}
		else {
			width = textSurface->w;
			height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return texture != NULL;
}

void BackGround::free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}
 
void BackGround::render(int x, int y, SDL_Rect* clips) {
	SDL_Rect renderQuad = { x, y, width, height };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, texture, clips, &renderQuad);
}

void BackGround::handleEvent(SDL_Event& e, int posX, int posY, BackGround& text_, bool& checkPlayed, Mix_Chunk* click_s) {
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		int pos_X_ = posX, pos_Y_ = posY;
		bool inside = true;

		if (x < posX) {
			inside = false;
		}
		else if (x > posX + text_.getWidth()) {
			inside = false;
		}
		else if (y < posY) {
			inside = false;
		}
		else if (y > posY + text_.getHeight()) {
			inside = false;
		}

		if (!inside) {
			posX = pos_X_;
			posY = pos_Y_;
		}
		else {
			switch (e.type) {
			case SDL_MOUSEMOTION:
				posX = pos_X_;
				posY = pos_Y_;
				break;
			case SDL_MOUSEBUTTONDOWN:
				posX -= 3;
				posY += 3;
				if (Mix_PlayingMusic() == 1) Mix_PauseMusic();
				Mix_PlayChannel(-1, click_s, 0);
				checkPlayed = true;
				break;
			case SDL_MOUSEBUTTONUP:
				posX = pos_X_;
				posY = pos_Y_;
				break;
			}
		}
	}
}

void BackGround::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, blending);
}

void BackGround::setAlphaMod(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

int BackGround::getWidth() {
	return width;
}

int BackGround::getHeight() {
	return height;
}

bool initSDL() {
	if (SDL_Init(SDL_INIT_AUDIO < 0)) {
		cout << "Could not initialize ! " << endl;
		return false;
	}
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Could not create window ! " << SDL_GetError();
		return false;
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			cout << "Could not create renderer ! " << SDL_GetError();
			return false;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

			int IMGflags = IMG_INIT_PNG;
			if (!(IMG_Init(IMGflags) & IMGflags)) {
				cout << "SDL_Image could not initialize ! " << IMG_GetError();
				return false;
			}

			if (TTF_Init() == -1) {
				cout << "SDL_ttf could not initialize ! " << TTF_GetError();
				return false;
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				cout << "SDL_mixer could not initialize ! " << endl;
				return false;
			}
		}
	}
	return true;
}

void close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}