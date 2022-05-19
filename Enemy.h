#ifndef ENEMY_H
#define ENEMY_H

#include "loadImage.h"

class Enemy : public BackGround {
private:
	int posX_e, posY_e;
	int velX_e, velY_e;
public:
	int speed_[3] = { 12, 13, 14 };

	Enemy();

	void setSpeed();
	void setSpeed2();
	void setSpeed3();

	void HandleMove_e();
	void HandleMove_e2();
	void HandleMove_e3();

	void setPos_x(int x);
	void setPos_y(int y);
	void render_e(Enemy* enemy__ = NULL, SDL_Rect* clips = NULL);

	void move_f(int speed, int loc, Mix_Chunk* sound = NULL);
	void setpos_XY_f(int x, int y);

	int getX() { return posX_e; }
	int getY() { return posY_e; }

	void re_L();
	void re_L2();
	void re_L3();

};

#endif