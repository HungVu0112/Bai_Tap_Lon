#ifndef PLAYER_
#define PLAYER_

#include "loadImage.h"
#include "bullet.h"
#include <vector>

class Player : public BackGround {
public:
	const int player_vel = 10;

	Player();

	void handleMove(SDL_Event& e, Player* player_, Mix_Chunk* bullet_s = NULL);
	void move(Player* player_ = NULL);
	void render_(Player* player_ = NULL);
	void renderPro_(Player& pro_t ,Player* player_ = NULL);
	void re_loc();

	void move_portal();

	int getX() { return posX; }
	int getY() { return posY; }

	void setb_list(vector <Bullet*> bullet_list_) { bullet_list = bullet_list_; }
	vector <Bullet*> getBullet_list() { return bullet_list; }

private:
	int posX;
	int posY;

	int velX;
	int velY;

	vector <Bullet*> bullet_list;
};

#endif