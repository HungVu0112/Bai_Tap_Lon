#include "Enemy.h"

Enemy::Enemy() {
	texture_E = NULL;
	posX_e = 0;
	posY_e = 700;
	velX_e = 0;

	width_e = 0;
	height_e = 0;
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
		else {
			width_e = loadedSurface->w;
			height_e = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture_E = newtexture;
	return texture_E != NULL;
}

void Enemy::render_e(SDL_Rect* clips, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { posX_e, posY_e, width_e, height_e };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, texture_E, clips, &renderQuad);
}

void Enemy::setSpeed() {
	velX_e = rand() % (25 - 23 + 1) + 23;
}

void Enemy::HandleMove_e(const int& x_bor, const int& y_bor) {
	setSpeed();
	posX_e -= velX_e;

	if (-posX_e >= 1000) {
		posX_e = x_bor;
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
