#include "loadImage.h"
#include "player.h"
#include "Enemy.h"
#include "bullet.h"

int Delay[MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3 };
int index = 0;
int flag = 0;
int DelayTime = 100;
int e_numb = 7, live_numb = 10;
int save = 0;
int Delay_Change_bg = 0;
////////////////////////////////////////////////////////////////////////////////////////
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
/////////////////////////////////////
bool initSDL();
bool Image();
void close();
//////////////////////////////////////////////////////////////
BackGround menu, menutext1, menutext2, menutext3, game_over_;
Uint8 a = 255;
int menutext1_X = 100, menutext1_Y = 100;
int menutext2_X = 150, menutext2_Y = 400;
int menutext3_X = 150, menutext3_Y = 500;
bool checkChangeMenu = false;
bool check_quit = false;
void changeBackGround1();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BackGround control_, controltext, livestext, control, heart, dots, changePoint, Roundtext, Live_re, pro_sign, Round1BackGround, Round2BackGround, Round3BackGround;
int controltext_X = 190, controltext_Y = 200;
int livestext_X = 750, livestext_Y = 200;
int changepoint_X = 1100, changepoint_Y = 630;
bool checkClicked = false;
void changeBackGround2();
/////////////////////////////////
Player* player_ = new Player();
BackGround Lives;
Player pro_t;
int BackGround_Speed = 0, BackGround_width = 6131;
///////////////////////////////////////////////////
Enemy* enemy_ = new Enemy[e_numb];
void e_show();
bool checkCollision(Player* player_ = NULL, Enemy* enemy = NULL);
///////////////////////////////////////////////////////////////////
stringstream Lives_Remain, Round_;
int round_num = 1;
bool check_l = false;
int lives_r = live_numb, Delay_d = 30, gameover_time_display = 100;
void control_display();
void check_live();
void changeBackGround3();
////////////////////////////////////////////////////////////////////
void menu_display();
void Round1_display();
void Round2_display();
void Round3_display();
void reset();
void changeBackGround4();
//////////////////////////
int bg_frame = 0;
SDL_Rect bg_clips[4];
void setClipsbg();
void setbg_motion();
void renderBG();
Enemy boss;
int boss_frame = 0;
SDL_Rect boss_clips[12];
void setClipsBoss();
void setboss_motion();
void renderboss();
void fire();
//////////////////////////////////
// MUSIC // 
Mix_Music* openMusic = NULL;
Mix_Chunk* click_s = NULL;
Mix_Chunk* crash = NULL;
Mix_Chunk* gameover = NULL;
////////////////////////////
int main(int argc, char* args[]) {
	srand(time(0));
	if (!initSDL()) {
		cout << "Could not initialize !! " << endl;
	}
	else if (!Image()) {
		cout << "Could not load menu background ! " << endl;
	}
	else {
		bool quit = false;
		SDL_Event e;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) quit = true;
				if (flag == 0) {
					menutext2.handleEvent(e, menutext2_X, menutext2_Y, menutext2, checkChangeMenu, click_s);
					menutext3.handleEvent(e, menutext3_X, menutext3_Y, menutext3, check_quit, click_s);
				}
				if (flag == 1) changePoint.handleEvent(e, changepoint_X, changepoint_Y, changePoint, checkClicked, click_s);
				player_->handleMove(e, player_);
			}

			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			SDL_RenderClear(renderer);

			// Quit game
			if (check_quit) quit = true;

			// Control Guide
			if (checkChangeMenu) {
				if (flag == 0) changeBackGround1();
				// Game Play
				if (checkClicked) {
					if (flag == 1) changeBackGround2();
					if (flag == 2) Round1_display();
					if (flag == 3) Round2_display();
					if (flag == 4) Round3_display();
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


bool Image() {
	// Music
	openMusic = Mix_LoadMUS("Sounds/opening.mp3");
	if (openMusic == NULL) {
		cout << "Could not load opening music ! " << endl;
		return false;
	}

	click_s = Mix_LoadWAV("Sounds/click_s.wav");
	if (click_s == NULL) {
		cout << "Could not load click sound ! " << endl;
		return false;
	}

	crash = Mix_LoadWAV("Sounds/boom.wav");
	if (crash == NULL) {
		cout << "Could not load crash sound ! " << endl;
		return false;
	}

	gameover = Mix_LoadWAV("Sounds/gameover.wav");
	if (gameover == NULL) {
		cout << "Could not load gameover sound ! " << endl;
		return false;
	}
	/////////////////////////////////////////////////////////
	// Menu background
	if (!menu.loadFromFile("Images/menutex.png")) {
		cout << "Could not load menu texture ! " << endl;
		return false;
	}
	else {
		menu.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	SDL_Color menutext1_color = { 0, 0, 0 };
	if (!menutext1.loadFromText("DODGE GAME", "Images/lazy2.ttf", menutext1_color, 150)) {
		cout << "Could not load text ! " << endl;
		return false;
	}

	SDL_Color menutext2_color = { 0, 0, 0 };
	if (!menutext2.loadFromText("PLAY", "Images/lazy2.ttf", menutext2_color, 70)) {
		cout << "Could not load text ! " << endl;
		return false;
	}

	SDL_Color menutext3_color = { 0, 0, 0 };
	if (!menutext3.loadFromText("EXIT", "Images/lazy2.ttf", menutext3_color, 70)) {
		cout << "Could not load text ! " << endl;
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Control Guide background
	if (!control_.loadFromFile("Images/control.png")) {
		cout << "Could not load control background ! " << endl;
		return false;
	}
	else {
		control_.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!control.loadFromFile("Images/arrowcontrol.png")) {
		cout << "Could not load arrowcontrol texture ! " << endl;
		return false;
	}

	if (!heart.loadFromFile("Images/heart.png")) {
		cout << "Could not load heart texture ! " << endl;
		return false;
	}

	if (!dots.loadFromFile("Images/dots.png")) {
		cout << "Could not load dots texture ! " << endl;
		return false;
	}

	if (!changePoint.loadFromFile("Images/plane.png")) {
		cout << "Could not load change texture ! " << endl;
		return false;
	}

	SDL_Color controltext_color = { 0, 0, 0 };
	if (!controltext.loadFromText("CONTROL", "Images/lazy2.ttf", controltext_color, 100)) {
		cout << "Could not load control text ! " << endl;
		return false;
	}

	SDL_Color livestex_color = { 0, 0, 0 };
	if (!livestext.loadFromText("LIVES", "Images/lazy2.ttf", livestex_color, 100)) {
		cout << "Could not load lives text ! " << endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Player Texture 
	if (!player_->loadFromFile("Images/plane.png")) {
		cout << "Could not load player texture ! " << endl;
		return false;
	}

	if (!Round1BackGround.loadFromFile("Images/bgPlay1.png")) {
		cout << "Could not load back ground ! " << endl;
		return false;
	}
	else {
		Round1BackGround.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!Round2BackGround.loadFromFile("images/bgPlay2.png")) {
		cout << "Could not load background ! " << endl;
		return false;
	}
	else {
		Round2BackGround.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!Round3BackGround.loadFromFile("images/bgPlay3.png")) {
		cout << "Could not load background ! " << endl;
		return false;
	}
	else setClipsbg();

	if (!Lives.loadFromFile("Images/heartreal.png")) {
		cout << "Could not load heart_2 texture ! " << endl;
		return false;
	}

	if (!pro_t.loadFromFile("Images/protection.png")) {
		cout << "Could not load protection texture ! " << endl;
		return false;
	}

	if (!pro_sign.loadFromFile("Images/pro_sign.png")) {
		cout << "Could not load sign ! " << endl;
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Enemy texture 
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		enemy__->loadFromFile("Images/icespike1.png");
		enemy__->setPos_x(i * 200);
	}

	if (!boss.loadFromFile("Images/boss.png")) {
		cout << "Could not load boss texture ! " << endl;
		return false;
	}
	else setClipsBoss();

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	SDL_Color game_over_color = { 188, 160, 194 };
	if (!game_over_.loadFromText("Game Over ! ", "Images/lazy2.ttf", game_over_color, 150)) {
		cout << "Could not load game over text ! " << endl;
		return false;
	}


	return true;
}

void menu_display() {
	if (Mix_PausedMusic() == 1) Mix_PlayMusic(openMusic, 0);
	if (Mix_PlayingMusic() == 0 ) Mix_PlayMusic(openMusic, 0);
	menu.render(0, 0);
	menutext1.render(menutext1_X, menutext1_Y);
	menutext2.render(menutext2_X, menutext2_Y);
	menutext3.render(menutext3_X, menutext3_Y);

	SDL_RenderPresent(renderer);

	menutext1_X -= Delay[index];
	menutext1_Y += Delay[index];
	if (index == (MAX - 1)) index = 0;
	else index++;
}

void control_display() {
	if (Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
	control_.render(0, 0);
	controltext.render(controltext_X, controltext_Y);
	control.render(250, 350);
	livestext.render(livestext_X, livestext_Y);
	heart.render(800, 360);
	dots.render(910, 600);
	changePoint.render(changepoint_X, changepoint_Y);
	SDL_RenderPresent(renderer);

	controltext_X -= Delay[index]; controltext_Y += Delay[index];
	livestext_X -= Delay[index]; livestext_Y += Delay[index];
	if (index == (MAX - 1)) index = 0;
	else index++;
}

void Round1_display() {
	player_->move(player_);
	Round1BackGround.render(BackGround_Speed, 0);

	while (DelayTime > 0) {
		Round_.str("");
		Round_ << "Round " << round_num;
		SDL_Color Round_Color = { 188, 160, 194 };
		if (!Roundtext.loadFromText(Round_.str().c_str(), "Images/lazy2.ttf", Round_Color, 150)) {
			cout << "Could not load Round text ! " << endl;
		}
		Roundtext.render(350, 250);
		SDL_RenderPresent(renderer);
		DelayTime--;
	}

	Lives.render(50, 20);
	player_->render_(player_);
	
	e_show();
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
	else BackGround_Speed -= 10;
}

void Round2_display() {
	player_->move(player_);
	Round2BackGround.render(BackGround_Speed, 0);

	while (DelayTime > 0) {
		Round_.str("");
		Round_ << "Round " << round_num;
		SDL_Color Round_Color = { 188, 160, 194 };
		if (!Roundtext.loadFromText(Round_.str().c_str(), "Images/lazy2.ttf", Round_Color, 150)) {
			cout << "Could not load Round text ! " << endl;
		}
		Roundtext.render(350, 250);
		SDL_RenderPresent(renderer);
		DelayTime--;
	}

	Lives.render(50, 20);
	player_->render_(player_);
	e_show();
	check_live();

	if (save == 240) {
		check_l = false;
		save = 0;
	}

	SDL_RenderPresent(renderer);

	if (-BackGround_Speed >= BackGround_width) {
		if (Delay_Change_bg < 60) BackGround_Speed = -BackGround_width;
		else changeBackGround4();
		Delay_Change_bg++;
	}
	else BackGround_Speed -= 10;
}

void changeBackGround1() {
	while (a > 0) {
		a -= 5;

		control_.render(0, 0);
		menu.setAlphaMod(a);
		menu.render(0, 0);
		SDL_RenderPresent(renderer);
	}
	flag++;
	a = 255;
}

void changeBackGround2() {
	while (a > 0) {
		a -= 5;

		Round1BackGround.render(0, 0);
		control_.setAlphaMod(a);
		control_.render(0, 0);
		SDL_RenderPresent(renderer);
	}
	flag++;
	a = 255;
}

void changeBackGround3() {
	while (a > 0) {
		a -= 5;

		Round2BackGround.render(0, 0);
		Round1BackGround.setAlphaMod(a);
		Round1BackGround.render(0, 0);
		SDL_RenderPresent(renderer);
	}

	flag++;
	a = 255;
	BackGround_Speed = 0; DelayTime = 100, Delay_Change_bg = 0;
	e_numb++;
	round_num++;

	enemy_ = new Enemy[e_numb];
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		enemy__->loadFromFile("Images/sand_spike.png");
		enemy__->setPos_x(i * 200);
	}

	player_->re_loc();
}

void changeBackGround4() {
	while (a > 0) {
		a -= 5;

		Round3BackGround.render(0, 0);
		Round2BackGround.setAlphaMod(a);
		Round2BackGround.render(0, 0);
		SDL_RenderPresent(renderer);
	}

	flag++;
	a = 255;
	BackGround_Speed = 0; DelayTime = 100;
	round_num++;
	player_->re_loc();
}

void reset() {
	flag = 0;
	lives_r = live_numb;
	DelayTime = 100;
	BackGround_Speed = 0;
	round_num = 1;
	e_numb = 7;
	gameover_time_display = 100;
	Delay_Change_bg = 0;

	checkChangeMenu = false;
	checkClicked = false;
	check_l = false;

	menu.setAlphaMod(a);
	control_.setAlphaMod(a);
	Round1BackGround.setAlphaMod(a);
	Round2BackGround.setAlphaMod(a);

	SDL_Color menutext2_c = { 0, 0, 0 };
	menutext2.loadFromText("PLAY AGAIN", "Images/lazy2.ttf", menutext2_c, 70);

	enemy_ = new Enemy[e_numb];
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		enemy__->loadFromFile("Images/icespike1.png");
		enemy__->setPos_x(i * 200);
	}

	player_->re_loc();
}

void e_show() {
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		if (enemy__ != NULL) {
			enemy__->HandleMove_e(screen_width, screen_height);
			enemy__->render_e(enemy__);
			if (BackGround_Speed == -BackGround_width) {
				if (enemy__->getX() < -200)
					enemy__->free();
			}
			else if (checkCollision(player_, enemy__)) {
				if (save == 0 && lives_r > 1) Mix_PlayChannel(-1, crash, 0);
				check_l = true;
				enemy__->re_L(screen_width);
			}
		}
	}
}

bool checkCollision(Player* player_, Enemy* enemy_) {
	int left_a = player_->getX();
	int right_a = player_->getX() + player_->getWidth();
	int top_a = player_->getY();
	int bottom_a = player_->getY() + player_->getHeight();

	int left_b = enemy_->getX();
	int right_b = enemy_->getX() + enemy_->getWidth();
	int top_b = enemy_->getY();
	int bottom_b = enemy_->getY() + enemy_->getHeight();

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
		pro_sign.render(150, 15);
		pro_t.renderPro_(pro_t ,player_);
		save++;
	}

	if (lives_r == 0) {
		Mix_PlayChannel(-1, gameover, 0);
		while (gameover_time_display > 0) {
			game_over_.render(250, 250);
			SDL_RenderPresent(renderer);
			gameover_time_display--;
		}
		reset();
	}

	Lives_Remain.str("");
	Lives_Remain << lives_r;
	SDL_Color l_Color = { 188, 160, 194 };
	if (!Live_re.loadFromText(Lives_Remain.str().c_str(), "Images/lazy2.ttf", l_Color, 30)) {
		cout << "Could not load live remain ! " << endl;
	}

	Live_re.render(120, 30);
}

void setClipsbg() {
	for (int i = 0; i < 4; i++) {
		bg_clips[i].x = i * 1200;
		bg_clips[i].y = 0;
		bg_clips[i].w = 1200;
		bg_clips[i].h = 689;
	}
}

void setbg_motion() {
	bg_frame++;
	if (bg_frame / 10 >= 4) bg_frame = 0;
}

void renderBG() {
	SDL_Rect* bg_cl = &bg_clips[bg_frame / 10];
	Round3BackGround.render(0, 0, bg_cl);
}

void setClipsBoss() {
	for (int i = 0; i < 12; i++) {
		boss_clips[i].x = i * 540;
		boss_clips[i].y = 0;
		boss_clips[i].w = 540;
		boss_clips[i].h = 420;
	}
}

void setboss_motion() {
	boss_frame++;
	if (boss_frame / 5 >= 12) boss_frame = 0;
}

void renderboss() {
	SDL_Rect* boss_cl = &boss_clips[boss_frame / 5];
	boss.render(630, 175, boss_cl);
}

void fire() {
	for (int i = 0; i < player_->getBullet_list().size(); i++) {
		vector<Bullet*> bullet_list = player_->getBullet_list();
		Bullet* bullet_ = bullet_list.at(i);
		if (bullet_ != NULL) {
			if (bullet_->ismove()) {
				bullet_->move();
				bullet_->render_b(bullet_);
			}
			else {
				if (bullet_ != NULL) {
					bullet_list.erase(bullet_list.begin() + i);
					player_->setb_list(bullet_list);

					delete bullet_;
					bullet_ = NULL;
				}
			}
		}
	}
}


void Round3_display() {
	player_->move(player_);
	renderBG();
	while (DelayTime > 0) {
		Round_.str("");
		Round_ << "Round " << round_num;
		SDL_Color Round_Color = { 188, 160, 194 };
		if (!Roundtext.loadFromText(Round_.str().c_str(), "Images/lazy2.ttf", Round_Color, 150)) {
			cout << "Could not load Round text ! " << endl;
		}
		Roundtext.render(350, 250);
		SDL_RenderPresent(renderer);
		DelayTime--;
	}

	Lives.render(50, 20);
	player_->render_(player_);
	fire();
	renderboss();
	check_live();

	if (save == 240) {
		check_l = false;
		save = 0;
	}

	SDL_RenderPresent(renderer);

	setbg_motion();
	setboss_motion();
}

