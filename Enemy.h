#ifndef ENEMY_H
#define ENEMY_H

#include "Loadimage_Func.h"

class Enemy {
private:
	SDL_Texture* texture_E;
	int posX_e, posY_e;
	int velX_e;

	int width_e, height_e;
public:
	Enemy();
	~Enemy();

	bool loadFromFile_e(string path, SDL_Renderer* renderer = NULL);
	void render_e(SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);
	void setSpeed();
	void HandleMove_e(const int& x_bor, const int& y_bor);
	void setPos_x(int x);

	int getX() { return posX_e; }
	int getY() { return posY_e; }

	void re_L(const int& x_bor);

	int getWidth_e() { return width_e; }
	int getHeight_e() { return height_e; }
};

#endif