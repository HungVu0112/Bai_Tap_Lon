#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <time.h>
#include <sstream>

using namespace std;

const int screen_width = 1200;
const int screen_height = 690;
const int MAX = 22;
const int enemy_numb = 5;


class Game {
private:
	SDL_Texture* texture;
	TTF_Font* font;
	int width;
	int height;
public:
	Game();
	~Game();

	bool loadFromFile(string path, SDL_Renderer* renderer = NULL);
	bool loadFromText(string text, string textFont, SDL_Color textColor, int size, SDL_Renderer* renderer = NULL);
	void free();

	void handleEvent(SDL_Event& e, int posX, int posY, Game& text_, bool& checkPlayed);
	void setBlendMode(SDL_BlendMode blending);
	void setAlphaMod(Uint8 alpha);

	void render(int x, int y, SDL_Rect* clips = NULL, SDL_Renderer* renderer = NULL);

	int getWidth();
	int getHeight();
};

#endif