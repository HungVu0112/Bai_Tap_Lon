#ifndef BULLET_
#define BULLET_

#include "loadImage.h"

class Bullet : public BackGround {
public:
	Bullet(int x, int y);	

	void move();
	
	void render_b(Bullet* bullet_ = NULL);

	bool ismove() { return ismoved_; }
	void setmove(bool ismoved) { ismoved_ = ismoved; }

	int getX_b() { return posX_b; }
	int getY_b() { return posY_b; }

private:
	int posX_b;
	int posY_b;

	int velX_b;

	bool ismoved_;
};

#endif