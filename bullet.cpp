#include "bullet.h"

Bullet::Bullet(int x, int y) {
	posX_b = x;
	posY_b = y;

	velX_b = 15;

	ismoved_ = false;
}

void Bullet::move() {
	posX_b += velX_b;

	if (posX_b > screen_width) {
		ismoved_ = false;
	}
}

void Bullet::render_b(Bullet* bullet_) {
	bullet_->render(posX_b, posY_b);
}