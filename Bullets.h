#ifndef BULLETS_H
#define BULLETS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Bullets {
private:
	SDL_Texture* B_texture;
	int posX_, posY_;

	bool is_move_;
public:
	Bullets();
	~Bullets();

	void setPOS(int x, int y);
	bool get_is_move() const { return is_move_; }
	void set_is_move(bool is_move) { is_move_ = is_move; }

	bool loadFromFile_B(string path, SDL_Renderer* renderer = NULL);
	void move_B(const int x_Bor, const int y_Bor);
	void render(SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);
};

#endif