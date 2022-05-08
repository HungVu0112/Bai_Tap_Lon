#include "Enemy.h"

Enemy::Enemy() {
	posX_e = 0;
	posY_e = 700;
	velX_e = 0;
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

void Enemy::render_e(Enemy* enemy__) {
	enemy__->render(posX_e, posY_e);
}

void Enemy::setPos_x(int x) {
	posX_e += x;
}

void Enemy::re_L(const int& x_bor) {
	posX_e = x_bor;
	posY_e = rand() % (610 - 100 + 1) + 100;
}
