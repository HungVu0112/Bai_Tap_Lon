#include "Enemy.h"

Enemy::Enemy() {
	posX_e = 0;
	posY_e = 700;
	velX_e = 0;
	velY_e = 0;
}

void Enemy::setSpeed() {
	velX_e = rand() % (25 - 23 + 1) + 23;
}

void Enemy::setSpeed2() {
	int s = rand() % (2 - 0 + 1) + 0;
	velX_e = speed_[s];
	velY_e = speed_[s];
}

void Enemy::setSpeed3() {
	velY_e = rand() % (15 - 12 + 1) + 12;
}

void Enemy::HandleMove_e() {
	setSpeed();
	posX_e -= velX_e;

	if (-posX_e >= 1200) {
		posX_e = screen_width;
		posY_e = rand() % (610 - 100 + 1) + 100;
	}
}

void Enemy::HandleMove_e2() {
	setSpeed2();
	posX_e -= velX_e;
	posY_e += velY_e;

	if (posY_e >= (screen_height + 1800)) {
		posX_e = rand() % (1400 - 300 + 1) + 300;
		posY_e = 0;
	}
}

void Enemy::HandleMove_e3() {
	setSpeed3();
	posY_e += velY_e;

	if (posY_e > (screen_height + 1000)) {
		posX_e = rand() % (600 - 10 + 1) + 10;
		posY_e = 0;
	}
}

void Enemy::render_e(Enemy* enemy__, SDL_Rect* clips) {
	enemy__->render(posX_e, posY_e, clips);
}

void Enemy::setPos_x(int x) {
	posX_e += x;
}

void Enemy::setPos_y(int y) {
	posY_e += y;
}

void Enemy::move_f(int speed, int loc, Mix_Chunk* sound) {
	if (posX_e == loc) Mix_PlayChannel(-1, sound, 0);
	
	posX_e -= speed;

	if (posX_e < -300) {
		posX_e = loc;
	}
}

void Enemy::setpos_XY_f(int x, int y) {
	posX_e = x;
	posY_e = y;
}

void Enemy::re_L() {
	posX_e = screen_width;
	posY_e = rand() % (610 - 100 + 1) + 100;
}

void Enemy::re_L2() {
	posX_e = rand() % (1000 - 300 + 1) + 300;
	posY_e = 0;
}

void Enemy::re_L3() {
	posX_e = rand() % (600 - 100 + 1) + 100;
	posY_e = 0;
}