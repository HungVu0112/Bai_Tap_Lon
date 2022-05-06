#ifndef PLAYER_H
#define PLEYER_H

#include "Loadimage_Func.h"

class Player {
private:
	SDL_Texture* texture_;
	int width_;
	int height_;

	int posX, posY;
	int velX, velY;
public:
	const int player_vel = 10;

	Player();

	bool loadFromFile_(string path, SDL_Renderer* renderer = NULL);
	void handleMove(SDL_Event& e, SDL_Renderer* renderer = NULL);
	void move(Player* player_ = NULL);
	void render_(int x, int y, SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);

	void renderPlayer(SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);
	void renderPro_(Player* player_ = NULL, SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);
	void re_loc();

	void free();

	int getWidth_() { return width_; }
	int getHeight_() { return height_; }

	int getX() { return posX; }
	int getY() { return posY; }
};

#endif