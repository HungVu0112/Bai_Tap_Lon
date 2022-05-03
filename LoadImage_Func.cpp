#include "Loadimage_Func.h"

Game::Game() {
	texture = NULL;
	font = NULL;
	width = 0;
	height = 0;
}

Game::~Game() {
	free();
}

bool Game::loadFromFile(string path, SDL_Renderer* renderer) {
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

bool Game::loadFromText(string text, string textFont, SDL_Color textColor, int size, SDL_Renderer* renderer) {
	free();

	font = TTF_OpenFont(textFont.c_str(), size);

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

void Game::free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Game::handleEvent(SDL_Event& e, int posX, int posY, Game& text_, bool& checkPlayed) {
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

void Game::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, blending);
}

void Game::setAlphaMod(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Game::render(int x, int y, SDL_Rect* clips, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { x, y, width, height };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, texture, clips, &renderQuad);
}

int Game::getWidth() {
	return width;
}

int Game::getHeight() {
	return height;
}
