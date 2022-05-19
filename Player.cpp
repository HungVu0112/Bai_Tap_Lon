#include "player.h"

Player::Player() {
	posX = 15;
	posY = screen_height / 2;

	velX = 0;
	velY = 0;
}

void Player::handleMove(SDL_Event& e, Player* player_, Mix_Chunk* bullet_s) {
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
		Mix_PlayChannel(-1, bullet_s, 0);
		Bullet* new_bullet = new Bullet(player_->getX() + player_->getWidth(), player_->getY());
		new_bullet->loadFromFile("Images/bullet.png");
		new_bullet->setmove(true);
		bullet_list.push_back(new_bullet);
	}
}

void Player::move(Player* player_) {
	posX += velX;

	if ((posX < 0) || (posX + player_->getWidth() > screen_width)) {
		posX -= velX;
	}

	posY += velY;

	if ((posY < 0) || (posY + player_->getHeight() > screen_height)) {
		posY -= velY;
	}
}

void Player::render_(Player* player_) {
	player_->render(posX, posY);
}

void Player::renderPro_(Player& pro_t ,Player* player_) {
	pro_t.render(player_->getX() - 21, player_->getY() - 19);
}


void Player::re_loc() {
	posX = 15;
	posY = screen_height / 2;
}

void Player::move_portal() {
	posX += 5;
}