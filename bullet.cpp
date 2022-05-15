#include "bullet.h"

Bullet::Bullet() {
	posX_b = 0;
	posY_b = 0;

	velX_b = 15;
}

void Bullet::move() {
	posX_b += velX_b;

	if (posX_b > screen_width) {
		free();
	}
}

void Bullet::render_b(Bullet* bullet_) {
	bullet_->render(posX_b, posY_b);
}