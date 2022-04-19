#include "Enemy.h"

Enemy::Enemy() {
	texture_E = NULL;
	posX_e = -10;
	posY_e = 700;
	velX_e = 23;
}

Enemy::~Enemy() {}

bool Enemy::loadFromFile_e(string path, SDL_Renderer* renderer) {
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
	texture_E = newtexture;
	return texture_E != NULL;
}

void Enemy::render_e(SDL_Rect* clips, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { posX_e, posY_e, 100, 47 };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, texture_E, clips, &renderQuad);
}

void Enemy::HandleMove_e(const int& x_bor, const int& y_bor) {
	posX_e -= velX_e;

	if (-posX_e >= x_bor) {
		posX_e = screen_width;
		posY_e = rand() % (610 - 100 + 1) + 100;
	}
}

void Enemy::setPos_x(int x) {
	posX_e += x;
}

void Enemy::re_L(const int& x_bor) {
	posX_e = x_bor;
	posY_e = rand() % (610 - 100 + 1) + 100;
}

