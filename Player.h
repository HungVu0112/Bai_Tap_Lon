#ifndef PLAYER_H
#define PLEYER_H

#include "Loadimage_Func.h"
#include "Bullets.h"
#include <vector>

class Player {
private:
	SDL_Texture* texture_;
	int width_;
	int height_;

	int posX, posY;
	int velX, velY;

	vector <Bullets*> bullet_list;
public:
	const int player_vel = 7;

	Player();

	bool loadFromFile_(string path, SDL_Renderer* renderer = NULL);
	void handleMove(SDL_Event& e, SDL_Renderer* renderer = NULL);
	void move(Player& player_);
	void render_(int x, int y, SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);
	
	void renderPlayer(SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);

	void free();

	int getWidth_();
	int getHeight_();

	void setbulletlist(vector <Bullets*> bullet_list_) { bullet_list = bullet_list_; }
	vector<Bullets*> getBulletlist() const { return bullet_list; }
};

#endif