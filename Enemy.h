#ifndef ENEMY_H
#define ENEMY_H

#include "loadImage.h"

class Enemy : public BackGround {
private:
	int posX_e, posY_e;
	int velX_e;
public:
	Enemy();

	void setSpeed();
	void HandleMove_e(const int& x_bor, const int& y_bor);
	void setPos_x(int x);
	void render_e(Enemy* enemy__ = NULL);

	int getX() { return posX_e; }
	int getY() { return posY_e; }

	void re_L(const int& x_bor);
};

#endif