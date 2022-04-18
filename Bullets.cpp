#include "Bullets.h"

Bullets::Bullets() {
	B_texture = NULL;
	posX_ = 0;
	posY_ = 0;
	
	is_move_ = false;
}

Bullets::~Bullets() {}

void Bullets::setPOS(int x, int y) {
	posX_ = x + 15;
	posY_ = y + 5;
}

bool Bullets::loadFromFile_B(string path, SDL_Renderer* renderer) {
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
		SDL_FreeSurface(loadedSurface);
	}
	B_texture = newtexture;
	return B_texture != NULL;
}

void Bullets::move_B(const int x_bor, const int y_bor) {
	posX_ += 20;

	if (posX_ > x_bor) is_move_ = false;
}

void Bullets::render(SDL_Rect* clips, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { posX_, posY_, 20, 20 };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, B_texture, clips, &renderQuad);
}