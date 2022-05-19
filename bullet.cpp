#include "bullet.h"

Bullet::Bullet(int x, int y) {
	posX_b = x;
	posY_b = y;

	velX_b = 15;

	ismoved_ = false;
}

void Bullet::move() {
	posX_b += velX_b;
	// 900 400 1000 500
	if ((posX_b > screen_width) || (posX_b >= 800 && 300 <= posY_b && posY_b < 400) || (posX_b >= 800 && 500 < posY_b && posY_b <= 600)) {
		ismoved_ = false;
	}
}

void Bullet::render_b(Bullet* bullet_) {
	bullet_->render(posX_b, posY_b);
}