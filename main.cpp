#include "Loadimage_Func.h"
#include "Player.h"
#include "Enemy.h"

int Delay[MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3 };
int index = 0;
int flag = 0;
int DelayTime = 100;
int e_numb = 6;
int save = 0;
int Delay_Change_bg = 0;
/////////////////////////////////////////////////////////////////////////////////////////
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
/////////////////////////////////////
bool initSDL();
bool loadBackGround();
void close();           
////////////////////////////////////////////////
Game menu, menutext1, menutext2, menutext3;
Uint8 a = 255;
int menutext1_X = 100, menutext1_Y = 100;
int menutext2_X = 150, menutext2_Y = 400;
bool checkChangeMenu = false;
void changeBackGround1();
////////////////////////////////////////////////////////////////////////////////////////////////////////
Game control_, controltext, livestext, control, heart, dots, changePoint, Roundtext, Live_re, pro_sign, Round1BackGround, Round2BackGround;
Uint8 b = 255;
int controltext_X = 190, controltext_Y = 200;
int livestext_X = 750, livestext_Y = 200;
int changepoint_X = 1100, changepoint_Y = 630;
bool checkClicked = false;
void changeBackGround2();
/////////////////////////////////////////////////////////////////
Player player_, Lives, pro_t;
int BackGround_Speed = 0, BackGround_width = 6131;
////////////////////////////////////////////////////
Enemy* enemy_ = new Enemy[e_numb];
void e_show();
bool checkCollision(Player& player_, Enemy* enemy);
stringstream Lives_Remain, Round_;
int round_num = 1;
bool check_l = false;
int lives_r = 10, Delay_d = 30;
Uint8 c = 255;
void check_live();
void changeBackGround3();
////////////////    GAME SETUP   /////////////////////////
void menu_display();
void control_display();
void Round1_display();
void Round2_display();
///////////////////////////////////////////////////////////

int main(int argc, char* args[]) {
	srand(time(0));
	if (!initSDL()) {
		cout << "Could not initialize !! " << endl;
	}
	else if (!loadBackGround()) {
		cout << "Could not load menu background ! " << endl;
	}
	else {
		bool quit = false;
		SDL_Event e;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) quit = true;
				if (flag == 0) menutext2.handleEvent(e, menutext2_X, menutext2_Y, menutext2, checkChangeMenu);
				if (flag == 1) changePoint.handleEvent(e, changepoint_X, changepoint_Y, changePoint, checkClicked);
				player_.handleMove(e, renderer);

			}

			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			SDL_RenderClear(renderer);

			// Control Guide
			if (checkChangeMenu) {
				if (flag == 0) changeBackGround1();
				// Game Play
				if (checkClicked) {
					if (flag == 1) changeBackGround2();
					if (flag == 2) Round1_display();
					if (flag == 3) Round2_display();
				}
				else {
					control_display();
				}
			}
			else {
				// Menu Background
				menu_display();
			}
		}
	}
	close();
	return 0;
}

bool initSDL() {
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Could not create window ! " << SDL_GetError();
		return false;
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			cout << "Could not create renderer ! " << SDL_GetError();
			return false;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

			int IMGflags = IMG_INIT_PNG;
			if (!(IMG_Init(IMGflags) & IMGflags)) {
				cout << "SDL_Image could not initialize ! " << IMG_GetError();
				return false;
			}

			if (TTF_Init() == -1) {
				cout << "SDL_ttf could not initialize ! " << TTF_GetError();
				return false;
			}
		}
	}
	return true;
}

bool loadBackGround() {

	// Menu background
	if (!menu.loadFromFile("Images/menutex.png", renderer)) {
		cout << "Could not load menu texture ! " << endl;
		return false;
	}
	else {
		menu.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	SDL_Color menutext1_color = { 0, 0, 0 };
	if (!menutext1.loadFromText("DODGE GAME", "Images/lazy2.ttf", menutext1_color, 150, renderer)) {
		cout << "Could not load text ! " << endl;
		return false;
	}

	SDL_Color menutext2_color = { 0, 0, 0 };
	if (!menutext2.loadFromText("PLAY", "Images/lazy2.ttf", menutext2_color, 70, renderer)) {
		cout << "Could not load text ! " << endl;
		return false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Control Guide background
	if (!control_.loadFromFile("Images/control.png", renderer)) {
		cout << "Could not load control background ! " << endl;
		return false;
	}
	else {
		control_.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!control.loadFromFile("Images/arrowcontrol.png", renderer)) {
		cout << "Could not load arrowcontrol texture ! " << endl;
		return false;
	}

	if (!heart.loadFromFile("Images/heart.png", renderer)) {
		cout << "Could not load heart texture ! " << endl;
		return false;
	}

	if (!dots.loadFromFile("Images/dots.png", renderer)) {
		cout << "Could not load dots texture ! " << endl;
		return false;
	}

	if (!changePoint.loadFromFile("Images/plane.png", renderer)) {
		cout << "Could not load change texture ! " << endl;
		return false;
	}

	SDL_Color controltext_color = { 0, 0, 0 };
	if (!controltext.loadFromText("CONTROL", "Images/lazy2.ttf", controltext_color, 100, renderer)) {
		cout << "Could not load control text ! " << endl;
		return false;
	}

	SDL_Color livestex_color = { 0, 0, 0 };
	if (!livestext.loadFromText("LIVES", "Images/lazy2.ttf", livestex_color, 100, renderer)) {
		cout << "Could not load lives text ! " << endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Player Texture 
	if (!player_.loadFromFile_("Images/plane.png", renderer)) {
		cout << "Could not load player texture ! " << endl;
		return false;
	}

	if (!Round1BackGround.loadFromFile("Images/bgPlay1.png", renderer)) {
		cout << "Could not load back ground ! " << endl;
		return false;
	}
	else {
		Round1BackGround.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!Round2BackGround.loadFromFile("images/bgPlay2.png", renderer)) {
		cout << "Could not load background ! " << endl;
		return false;
	}

	if (!Lives.loadFromFile_("Images/heartreal.png", renderer)) {
		cout << "Could not load heart_2 texture ! " << endl;
		return false;
	}

	if (!pro_t.loadFromFile_("Images/protection.png", renderer)) {
		cout << "Could not load protection texture ! " << endl;
		return false;
	}

	if (!pro_sign.loadFromFile("Images/pro_sign.png", renderer)) {
		cout << "Could not load sign ! " << endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Enemy texture 
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		enemy__->loadFromFile_e("Images/icespike1.png", renderer);
		enemy__->setPos_x(i * 200);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

void close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void menu_display() {
	menu.render(0, 0, NULL, renderer);
	menutext1.render(menutext1_X, menutext1_Y, NULL, renderer);
	menutext2.render(menutext2_X, menutext2_Y, NULL, renderer);

	SDL_RenderPresent(renderer);

	menutext1_X -= Delay[index];
	menutext1_Y += Delay[index];
	if (index == (MAX - 1)) index = 0;
	else index++;
}

void control_display() {
	control_.render(0, 0, NULL, renderer);
	controltext.render(controltext_X, controltext_Y, NULL, renderer);
	control.render(250, 350, NULL, renderer);
	livestext.render(livestext_X, livestext_Y, NULL, renderer);
	heart.render(800, 360, NULL, renderer);
	dots.render(910, 600, NULL, renderer);
	changePoint.render(changepoint_X, changepoint_Y, NULL, renderer);
	SDL_RenderPresent(renderer);

	controltext_X -= Delay[index]; controltext_Y += Delay[index];
	livestext_X -= Delay[index]; livestext_Y += Delay[index];
	if (index == (MAX - 1)) index = 0;
	else index++;
}

void Round1_display() {
	player_.move(player_);
	Round1BackGround.render(BackGround_Speed, 0, NULL, renderer);

	while (DelayTime > 0) {
		Round_.str("");
		Round_ << "Round " << round_num;
		SDL_Color Round_Color = { 188, 160, 194 };
		if (!Roundtext.loadFromText(Round_.str().c_str(), "Images/lazy2.ttf", Round_Color, 150, renderer)) {
			cout << "Could not load Round text ! " << endl;
		}
		Roundtext.render(350, 250, NULL, renderer);
		SDL_RenderPresent(renderer);
		DelayTime--; 
	}

	Lives.render_(50, 20, NULL, renderer);
	player_.renderPlayer(NULL, renderer);
	if (-BackGround_Speed < BackGround_width) e_show();
	check_live();

	if (save == 240) {
		check_l = false;
		save = 0;
	}

	SDL_RenderPresent(renderer);

	if (-BackGround_Speed >= BackGround_width) {
		if (Delay_Change_bg < 60) BackGround_Speed = -BackGround_width;
		else changeBackGround3();
		Delay_Change_bg++;
	}
	else BackGround_Speed -= 2;
}

void Round2_display() {
	player_.move(player_);
	Round2BackGround.render(BackGround_Speed, 0, NULL, renderer);

	while (DelayTime > 0) {
		Round_.str("");
		Round_ << "Round " << round_num;
		SDL_Color Round_Color = { 188, 160, 194 };
		if (!Roundtext.loadFromText(Round_.str().c_str(), "Images/lazy2.ttf", Round_Color, 150, renderer)) {
			cout << "Could not load Round text ! " << endl;
		}
		Roundtext.render(350, 250, NULL, renderer);
		SDL_RenderPresent(renderer);
		DelayTime--;
	}

	Lives.render_(50, 20, NULL, renderer);
	player_.renderPlayer(NULL, renderer);
	if (-BackGround_Speed < BackGround_width) e_show();
	check_live();

	if (save == 240) {
		check_l = false;
		save = 0;
	}

	SDL_RenderPresent(renderer);

	if (-BackGround_Speed >= BackGround_width) BackGround_Speed = -BackGround_width;
	else BackGround_Speed -= 2;
}

void changeBackGround1() {
	while (a > 0) {
		a -= 5;

		control_.render(0, 0, NULL, renderer);
		menu.setAlphaMod(a);
		menu.render(0, 0, NULL, renderer);
		SDL_RenderPresent(renderer);
	}
	flag++;
}

void changeBackGround2() {
	while (b > 0) {
		b -= 5;

		Round1BackGround.render(0, 0, NULL, renderer);
		control_.setAlphaMod(b);
		control_.render(0, 0, NULL, renderer);
		SDL_RenderPresent(renderer);
	}
	flag++;
}

void changeBackGround3() {
	while (c > 0) {
		c -= 5;

		Round2BackGround.render(0, 0, NULL, renderer);
		Round1BackGround.setAlphaMod(c);
		Round1BackGround.render(0, 0, NULL, renderer);
		SDL_RenderPresent(renderer);
	}
	flag++;
	BackGround_Speed = 0; DelayTime = 100;
	e_numb++;
	enemy_ = new Enemy[e_numb];
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		enemy__->loadFromFile_e("Images/sand_spike.png", renderer);
		enemy__->setPos_x(i * 200);
	}
	round_num++;
}

void e_show() {
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		if (enemy__ != NULL) {
			enemy__->HandleMove_e(screen_width, screen_height);
			enemy__->render_e(NULL, renderer);
			if (checkCollision(player_, enemy__)) {
				check_l = true;
				enemy__->re_L(screen_width);
			}
		}
	}
}

bool checkCollision(Player& player_, Enemy* enemy_) {
	int left_a = player_.getX();
	int right_a = player_.getX() + player_.getWidth_();
	int top_a = player_.getY();
	int bottom_a = player_.getY() + player_.getHeight_();

	int left_b = enemy_->getX();
	int right_b = enemy_->getX() + enemy_->getWidth_e();
	int top_b = enemy_->getY();
	int bottom_b = enemy_->getY() + enemy_->getHeight_e();

	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

void check_live() {
	if (check_l) {
		if (save == 0) lives_r--;
		pro_sign.render(150, 15, NULL, renderer);
		pro_t.renderPro_(player_, NULL, renderer);
		save++;
	}

	Lives_Remain.str("");
	Lives_Remain << lives_r;
	SDL_Color l_Color = { 188, 160, 194 };
	if (!Live_re.loadFromText(Lives_Remain.str().c_str(), "Images/lazy2.ttf", l_Color, 30, renderer)) {
		cout << "Could not load live remain ! " << endl;
	}

	Live_re.render(120, 30, NULL, renderer);
}