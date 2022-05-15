#ifndef BULLET_
#define BULLET_

#include "loadImage.h"
#include "player.h"

class Bullet : public BackGround {
public:
	Bullet();	

	void move();
	void render_b(Bullet* bullet_ = NULL);

	int getX_b() { return posX_b; }
	int getY_b() { return posY_b; }

private:
	int posX_b;
	int posY_b;

	int velX_b;
};

#endif