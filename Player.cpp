#include "Player.h"

Player::Player() {
	texture_ = NULL;
	width_ = 0;
	height_ = 0;

	posX = 15; posY = screen_height / 2;
	velX = 0; velY = 0;
}

bool Player::loadFromFile_(string path, SDL_Renderer* renderer) {
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
			width_ = loadedSurface->w;
			height_ = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	texture_ = newtexture;
	return texture_ != NULL;
}

void Player::handleMove(SDL_Event& e, SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY -= player_vel; break;
		case SDLK_DOWN: velY += player_vel; break;
		case SDLK_RIGHT: velX += player_vel; break;
		case SDLK_LEFT: velX -= player_vel; break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY += player_vel; break;
		case SDLK_DOWN: velY -= player_vel; break;
		case SDLK_RIGHT: velX -= player_vel; break;
		case SDLK_LEFT: velX += player_vel; break;
		}
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0) {
		Bullets* bullet = new Bullets();
		bullet->loadFromFile_B("Images/bullet.png", renderer);
		bullet->setPOS(posX, posY);
		bullet->set_is_move(true);
		bullet_list.push_back(bullet);
	}
}

void Player::move(Player& player_) {
	posX += velX;

	if ((posX < 0) || (posX + player_.getWidth_() > screen_width)) {
		posX -= velX;
	}

	posY += velY;

	if ((posY < 0) || (posY + player_.getHeight_() > screen_height)) {
		posY -= velY;
	}
}

void Player::render_(int x, int y, SDL_Rect* clips, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { x, y, width_, height_ };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, texture_, clips, &renderQuad);
}

void Player::renderPlayer(SDL_Rect* clips, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { posX, posY, width_, height_ };
	if (clips != NULL) {
		renderQuad.w = clips->w;
		renderQuad.h = clips->h;
	}
	SDL_RenderCopy(renderer, texture_, clips, &renderQuad);
}

void Player::free() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

int Player::getWidth_() {
	return width_;
}

int Player::getHeight_() {
	return height_;
}
