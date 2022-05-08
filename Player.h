#ifndef PLAYER_
#define PLAYER_

#include "loadImage.h"

class Player : public BackGround {
public:
	const int player_vel = 10;

	Player();

	void handleMove(SDL_Event& e);
	void move(Player* player_ = NULL);
	void render_(Player* player_ = NULL);
	void renderPro_(Player& pro_t ,Player* player_ = NULL);
	void re_loc();

	int getX() { return posX; }
	int getY() { return posY; }
private:
	int posX;
	int posY;

	int velX;
	int velY;
};

#endif