#ifndef LOAD_IMAGE_
#define LOAD_IMAGE_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <time.h>

using namespace std;

const int screen_width = 1200;
const int screen_height = 690;
const int MAX = 22;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

extern bool initSDL();
extern void close();

class BackGround {  
public:
	BackGround();
	~BackGround();

	bool loadFromFile(string path);
	bool loadFromText(string text, string textFont, SDL_Color textColor, int size);
	void free();

	void render(int x, int y, SDL_Rect* clips = NULL);

	void handleEvent(SDL_Event& e, int posX, int posY, BackGround& text_, bool& checkPlayed);
	void setBlendMode(SDL_BlendMode blending);
	void setAlphaMod(Uint8 alpha);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	int width;
	int height;
};

#endif

