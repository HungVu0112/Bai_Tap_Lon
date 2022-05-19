#include "loadImage.h"
#include "player.h"
#include "Enemy.h"
#include "bullet.h"

int Delay[MAX] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3 };
int index = 0;
int flag = 0;
////////////////////////////////////////////////////////////////////////////////////////
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
/////////////////////////////////////
bool initSDL();
bool Image();
void close();
/////////////////////////////////////////////////////////////
// Menu function // 
BackGround menu, menutext1, menutext2, menutext3,boss_death;
Uint8 a = 255;
int menutext1_X = 100, menutext1_Y = 100;
int menutext2_X = 150, menutext2_Y = 400;
int menutext3_X = 150, menutext3_Y = 500;
bool checkChangeMenu = false;
bool check_quit = false;
void changeBackGround1();
void menu_display();
////////////////////////////////////////////////////////////////////////////////
// Control function // 
BackGround control_, controltext, livestext, control, heart, dots, changePoint;
int controltext_X = 190, controltext_Y = 200;
int livestext_X = 750, livestext_Y = 200;
int changepoint_X = 1100, changepoint_Y = 630;
bool checkClicked = false;
void changeBackGround2();
void control_display();
////////////////////////////////////////////////////////////////////////////////////
// Round function // 
BackGround  Round1BackGround, Round2BackGround, Round3BackGround, Lives, Roundtext;
int BackGround_Speed = 0, BackGround_width = 6131;
stringstream Lives_Remain, Round_;
int round_num = 1;
bool check_l = false;
int DelayTime = 100;
int Delay_Change_bg = 0;

// Round 
void Round1_display();
void Round2_display();
void Round3_display();

// Check live 
void check_live();
int save = 0;

// Change background
void changeBackGround3();
void changeBackGround4();

// Final round function 
int bg_frame = 0;
int delay_roar = 0;
SDL_Rect bg_clips[4];
void setClipsbg();
void setbg_motion();
void renderBG();

// Boss health remain 
int boss_health = 200;
stringstream b_remain;
bool checkDam = false;
BackGround B_Health;
void checkb_remain();

// Guide
BackGround GuideText;
int guide_delay = 60;
void Guide();
///////////////////////////////
// boss death // 
int delay_death = 0;
SDL_Rect boss_death_clips[10];
int boss_d_frame = 0;
void setboss_d_clips();
void set_boss_d_motion();
void render_boss_death();
////////////////////////////////
// Portal function // 
BackGround  portal_1, portal_2;

// Sand Portal
SDL_Rect portal1_clips[9];
int portal1_frame = 0;
void setportal1Clips();
void set_portal1_motion();
void renderportal1();

// Boss Portal
SDL_Rect portal2_clips[9];
int portal2_frame = 0;
void setportal2Clips();
void set_portal2_motion();
void renderportal2();
//////////////////////////
// Shield function // 
BackGround  pro_sign;
Player pro_t;
/////////////////////////////////
// Gameover function // 
BackGround game_over_;
int gameover_time_display = 120;
/////////////////////////////////
// Victory function //
BackGround victory;
int victory_Delay = 120;
/////////////////////////
// Reset function // 
void reset();
/////////////////////
// Live function //
BackGround Live_re;
////////////////////////////////
// Player function // 
Player* player_ = new Player();
void fire();
int live_numb = 10;
int lives_r = live_numb;
int check_fire = 0;
///////////////////////////////////
// Enemy function //
int e_numb = 7;
Enemy* enemy_ = new Enemy[e_numb];
void e_show();
void e_show2();
void e_show3();
// Boss
Enemy boss;
int boss_frame = 0;
SDL_Rect boss_clips[12];
void setClipsBoss();
void setboss_motion();
void renderboss();

// Boss Fire ball
Enemy* boss_fire = new Enemy();
int boss_fire_frame = 0;
SDL_Rect boss_fire_clips[9];
void setBall_Clips();
void setBoss_fire_motion();
void renderboss_fire();

// Tornado
Enemy* tornado = new Enemy();
int tornado_frame = 0;
SDL_Rect tornado_clips[10];
void setTornado_clips();
void setTornado_motion();
void renderTornado();
/////////////////////////////////////////////////////////////////////////////////////////////
// Check Collision // 
bool checkCollision(int x, int y, int w, int h, Player* player_ = NULL, Enemy* enemy = NULL);
bool checkBulletCollision(Bullet* bullet_);
/////////////////////////////
// MUSIC // 
Mix_Music* openingMusic = NULL;
Mix_Music* Round1Music = NULL;
Mix_Music* Round2Music = NULL;
Mix_Music* Round3Music = NULL;
Mix_Chunk* dragon_r = NULL;
Mix_Chunk* dragon_d = NULL;
Mix_Chunk* victory_s = NULL;
Mix_Chunk* tornado_s = NULL;
Mix_Chunk* portal_s = NULL;
Mix_Chunk* bullet_s = NULL;
Mix_Chunk* fireball_s = NULL;
Mix_Chunk* click_s = NULL;
Mix_Chunk* crash = NULL;
Mix_Chunk* gameover = NULL;
////////////////////////////
// MAIN FUNCTION //
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
					menutext2.handleEvent(e, menutext2_X, menutext2_Y, menutext2, checkChangeMenu, flag, click_s);
					menutext3.handleEvent(e, menutext3_X, menutext3_Y, menutext3, check_quit, flag, click_s);
				}
				if (flag == 1) changePoint.handleEvent(e, changepoint_X, changepoint_Y, changePoint, checkClicked, flag, click_s);
				player_->handleMove(e, player_, bullet_s);
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

// Load Image funtion
bool Image() {
	// Music
	openingMusic = Mix_LoadMUS("Sounds/opening.mp3");
	if (openingMusic == NULL) {
		cout << "Could not load opening music ! " << endl;
		return false;
	}

	Round1Music = Mix_LoadMUS("Sounds/Round1_s.mp3");
	if (Round1Music == NULL) {
		cout << "Could not load round 1 music ! " << endl;
		return false;
	}

	Round2Music = Mix_LoadMUS("Sounds/Round2_s.mp3");
	if (Round2Music == NULL) {
		cout << "Could not load round 2 music ! " << endl;
		return false;
	}

	Round3Music = Mix_LoadMUS("Sounds/BossRound_s.mp3");
	if (Round3Music == NULL) {
		cout << "Could not load round 3 music ! " << endl;
		return false;
	}

	dragon_d = Mix_LoadWAV("Sounds/dragon_d.wav");
	if (dragon_d == NULL) {
		cout << "Could not load dragon death sound ! " << endl;
		return false;
	}

	dragon_r = Mix_LoadWAV("Sounds/dragon_r.wav");
	if (dragon_r == NULL) {
		cout << "Could not load dragon roar ! " << endl;
		return false;
	}

	victory_s = Mix_LoadWAV("Sounds/victory.wav");
	if (victory_s == NULL) {
		cout << "Could not load victory sound ! " << endl;
		return false;
	}

	tornado_s = Mix_LoadWAV("Sounds/storm.wav");
	if (tornado_s == NULL) {
		cout << "Could not load tornado sound ! " << endl;
		return false;
	}

	portal_s = Mix_LoadWAV("Sounds/portal.wav");
	if (portal_s == NULL) {
		cout << "Could not load portal sound ! " << endl;
		return false;
	}

	bullet_s = Mix_LoadWAV("Sounds/bullet_s.wav");
	if (bullet_s == NULL) {
		cout << "Could not load bullet sound ! " << endl;
		return false;
	}

	fireball_s = Mix_LoadWAV("Sounds/fireball_s.wav");
	if (fireball_s == NULL) {
		cout << "Could not load fire ball sound ! " << endl;
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

	SDL_Color GuideColor = { 188, 160, 194 };
	if (!GuideText.loadFromText("Press SPACE to shoot ! ", "Images/lazy2.ttf", GuideColor, 90)) {
		cout << "Could not load text ! " << endl;
		return false;
	}

	if (!boss_fire->loadFromFile("Images/boss_fire.png")) {
		cout << "Could not load boss fire ball texture ! " << endl;
		return false;
	}
	else {
		setBall_Clips();
		boss_fire->setpos_XY_f(680, 380);
	}
	
	if (!tornado->loadFromFile("Images/tornado.png")) {
		cout << "Could not load tornado texture ! " << endl;
		return false;
	}
	else {
		setTornado_clips();
		tornado->setpos_XY_f(1600, -150);
	}

	SDL_Color victory_Color = { 188, 160, 194 };
	if (!victory.loadFromText("VICTORY", "Images/lazy2.ttf", victory_Color, 150)) {
		cout << "Could not load victory text ! " << endl;
		return false;
	}

	if (!portal_1.loadFromFile("Images/portal.png")) {
		cout << "Could not load portal texture ! " << endl;
		return false;
	}
	else setportal1Clips();

	if (!portal_2.loadFromFile("Images/portal2.png")) {
		cout << "Could not load portal texture ! " << endl;
		return false;
	}
	else setportal2Clips();

	if (!boss_death.loadFromFile("Images/explo.png")) {
		cout << "Could not load explo texture ! " << endl;
		return false;
	}
	else setboss_d_clips();

	return true;
}

// Render menu and control function
void menu_display() {
	if (Mix_PlayingMusic() == 0 ) Mix_PlayMusic(openingMusic, 0);
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

// Render round's gameplay function
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

	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(Round1Music, 0);

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
		else {
			if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
			player_->re_loc();
			Mix_PlayChannel(-1, portal_s, 0);
			while (player_->getX() <= 900){
				Round1BackGround.render(BackGround_Speed, 0);
				player_->move_portal();
				renderportal1();
				player_->render_(player_);
				SDL_RenderPresent(renderer);
				set_portal1_motion();
			}
			Mix_HaltChannel(-1);
			changeBackGround3();
		}
		Delay_Change_bg++;
	}
	else BackGround_Speed -= 3;
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
	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(Round2Music, 0);

	Lives.render(50, 20);
	player_->render_(player_);
	e_show2();
	check_live();

	if (save == 240) {
		check_l = false;
		save = 0;
	}

	SDL_RenderPresent(renderer);

	if (-BackGround_Speed >= BackGround_width) {
		if (Delay_Change_bg < 60) BackGround_Speed = -BackGround_width;
		else {
			if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
			player_->re_loc();
			Mix_PlayChannel(-1, portal_s, 0);
			while (player_->getX() <= 900) {
				Round2BackGround.render(BackGround_Speed, 0);
				player_->move_portal();
				renderportal2();
				player_->render_(player_);
				SDL_RenderPresent(renderer);
				set_portal2_motion();
			}
			Mix_HaltChannel(-1);
			changeBackGround4();
		}
		Delay_Change_bg++;
	}
	else BackGround_Speed -= 3;
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

	Guide();

	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(Round3Music, 0);

	if (boss_health > 0) {

		if(delay_roar == 0) Mix_PlayChannel(-1, dragon_r, 0);

		Lives.render(50, 20);
		player_->render_(player_);
		renderboss();
		fire();

		if (check_fire == 1) {
			if (boss_health <= 100) e_show3();
			if (boss_health <= 50) renderTornado();
			if (checkCollision(tornado->getX() + 120, tornado->getY(), 443, 1000, player_, NULL)) {
				if (save == 0) Mix_PlayChannel(-1, crash, 0);
				check_l = true;
			}

			renderboss_fire();
			if (checkCollision(boss_fire->getX(), boss_fire->getY(), 180, 133, player_, NULL)) {
				if (save == 0) Mix_PlayChannel(-1, crash, 0);
				check_l = true;
			}
		}
		check_live();

		if (save == 240) {
			check_l = false;
			save = 0;
		}

		checkb_remain();
	}
	else {
		if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
		Mix_HaltChannel(-1);
		player_->re_loc();
		if (delay_death < 50) {
			Mix_PlayChannel(-1, dragon_d, 0);
			while (delay_death < 50) {
				renderBG();
				player_->render_(player_);
				render_boss_death();
				SDL_RenderPresent(renderer);
				setbg_motion();
				set_boss_d_motion();
				delay_death++;
			}
		}
		if (delay_death == 50) {
			Mix_PlayChannel(-1, victory_s, 0);
			while (victory_Delay > 0) {
				renderBG();
				victory.render(250, 300);
				SDL_RenderPresent(renderer);
				setbg_motion();
				victory_Delay--;
			}
		}
		Mix_HaltChannel(-1);
		reset();
	}

	SDL_RenderPresent(renderer);

	delay_roar = 1;
	setbg_motion();
	setboss_motion();
	setBoss_fire_motion();
	setTornado_motion();
}

// Change background function
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
		enemy__->setPos_y(i * 200);
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
	e_numb = 3;

	enemy_ = new Enemy[e_numb];
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		enemy__->loadFromFile("Images/boss_spike.png");
		enemy__->setPos_y(i * 200);
	}

	player_->re_loc();
}

// Reset function
void reset() {
	flag = 0;
	lives_r = live_numb;
	DelayTime = 100;
	BackGround_Speed = 0;
	round_num = 1;
	e_numb = 7;
	gameover_time_display = 120;
	Delay_Change_bg = 0;
	guide_delay = 60;
	victory_Delay = 120;
	boss_health = 200;
	save = 0;
	check_fire = 0;
	delay_death = 0;
	delay_roar = 0;

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

// Render spike function
void e_show() {
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		if (enemy__ != NULL) {
			enemy__->HandleMove_e();
			enemy__->render_e(enemy__);
			if (BackGround_Speed == -BackGround_width) {
				if (enemy__->getX() < -200)
					enemy__->free();
			}
			else if (checkCollision(0, 0, 0, 0, player_, enemy__)) {
				if (save == 0 && lives_r > 1) Mix_PlayChannel(-1, crash, 0);
				check_l = true;
				enemy__->re_L();
			}
		}
	}
}

void e_show2() {
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		if (enemy__ != NULL) {
			enemy__->HandleMove_e2();
			enemy__->render_e(enemy__);
			if (BackGround_Speed == -BackGround_width) {
				if (enemy__->getY() > (screen_height + 300))
					enemy__->free();
			}
			else if (checkCollision(0, 0, 0, 0, player_, enemy__)) {
				if (save == 0 && lives_r > 1) Mix_PlayChannel(-1, crash, 0);
				check_l = true;
				enemy__->re_L2();
			}
		}
	}
}

void e_show3() {
	for (int i = 0; i < e_numb; i++) {
		Enemy* enemy__ = (enemy_ + i);
		if (enemy__ != NULL) {
			enemy__->HandleMove_e3();
			enemy__->render_e(enemy__);
			if (BackGround_Speed == -BackGround_width) {
				if (enemy__->getY() > (screen_height + 1000))
					enemy__->free();
			}
			else if (checkCollision(0, 0, 0, 0, player_, enemy__)) {
				if (save == 0 && lives_r > 1) Mix_PlayChannel(-1, crash, 0);
				check_l = true;
				enemy__->re_L3();
			}
		}
	}
}

// Check collision function
bool checkCollision(int x, int y, int w, int h, Player* player_, Enemy* enemy_) {
	int left_a = player_->getX();
	int right_a = player_->getX() + player_->getWidth();
	int top_a = player_->getY();
	int bottom_a = player_->getY() + player_->getHeight();

	int left_b, right_b, top_b, bottom_b;

	if (enemy_ != NULL) {
		 left_b = enemy_->getX();
		 right_b = enemy_->getX() + enemy_->getWidth();
		 top_b = enemy_->getY();
		 bottom_b = enemy_->getY() + enemy_->getHeight();
	}
	else {
		left_b = x;
		right_b = x + w;
		top_b = y;
		bottom_b = y + h;
	}

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

bool checkBulletCollision(Bullet* bullet_) {
	int left_a = bullet_->getX_b();
	int right_a = bullet_->getX_b() + bullet_->getWidth();
	int top_a = bullet_->getY_b();
	int bottom_a = bullet_->getY_b() + bullet_->getHeight();

	int left_b = 800;
	int right_b = 800 + 100;
	int top_b = 400;
	int bottom_b = 400 + 100;

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

// Check live function
void check_live() {
	if (check_l) {
		if (save == 0) lives_r--;
		pro_sign.render(150, 15);
		pro_t.renderPro_(pro_t ,player_);
		save++;
	}

	if (lives_r == 0) {
		if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
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

// Render boss death's scene function
void setboss_d_clips() {
	for (int i = 0; i < 10; i++) {
		boss_death_clips[i].x = i * 256;
		boss_death_clips[i].y = 0;
		boss_death_clips[i].w = 256;
		boss_death_clips[i].h = 280;
	}
}

void set_boss_d_motion() {
	boss_d_frame++;
	if (boss_d_frame / 5 >= 10) boss_d_frame = 0;
}

void render_boss_death() {
	SDL_Rect* boss_death_cl = &boss_death_clips[boss_d_frame / 5];
	boss_death.render(780, 340, boss_death_cl);
}

// Render sand portal function
void setportal1Clips() {
	for (int i = 0; i < 9; i++) {
		portal1_clips[i].x = i * 498;
		portal1_clips[i].y = 0;
		portal1_clips[i].w = 498;
		portal1_clips[i].h = 498;
	}
}

void set_portal1_motion() {
	portal1_frame++;
	if (portal1_frame / 4 >= 9) portal1_frame = 0;
}

void renderportal1() {
	SDL_Rect* portal_cl = &portal1_clips[portal1_frame / 4];
	portal_1.render(680, 90, portal_cl);
}

// Render boss portal function
void setportal2Clips() {
	for (int i = 0; i < 9; i++) {
		portal2_clips[i].x = i * 498;
		portal2_clips[i].y = 0;
		portal2_clips[i].w = 498;
		portal2_clips[i].h = 498;
	}
}

void set_portal2_motion() {
	portal2_frame++;
	if (portal2_frame / 4 >= 9) portal2_frame = 0;
}

void renderportal2() {
	SDL_Rect* portal_cl_ = &portal2_clips[portal2_frame / 4];
	portal_2.render(680, 90, portal_cl_);
}

// Render final round background function
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

// Render boss function
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

// Render fire ball function
void setBall_Clips() {
	for (int i = 0; i < 9; i++) {
		boss_fire_clips[i].x = i * 200;
		boss_fire_clips[i].y = 0;
		boss_fire_clips[i].w = 200;
		boss_fire_clips[i].h = 133;
 	}
}

void setBoss_fire_motion() {
	boss_fire_frame++;
	if (boss_fire_frame / 4 >= 9) boss_fire_frame = 0;
}

void renderboss_fire() {
	SDL_Rect* ball_cl = &boss_fire_clips[boss_fire_frame / 4];
	boss_fire->move_f(15, 680, fireball_s);
	boss_fire->render_e(boss_fire, ball_cl);
}

// Render fireball function
void setTornado_clips() {
	for (int i = 0; i < 10; i++) {
		tornado_clips[i].x = i * 443;
		tornado_clips[i].y = 0;
		tornado_clips[i].w = 443;
		tornado_clips[i].h = 1000;
	}
}

void setTornado_motion() {
	tornado_frame++;
	if (tornado_frame / 4 >= 10) tornado_frame = 0;
}

void renderTornado() {
	SDL_Rect* tornado_cl = &tornado_clips[tornado_frame / 4];
	tornado->move_f(5, 1600, tornado_s);
	tornado->render_e(tornado, tornado_cl);
}

// Launch bullet & guide and check boss's health remaining function
void fire() {
	for (int i = 0; i < player_->getBullet_list().size(); i++) {
		vector<Bullet*> bullet_list = player_->getBullet_list();
		Bullet* bullet_ = bullet_list.at(i);
		if (bullet_ != NULL) {
			if (bullet_->ismove()) {
				bullet_->move();
				bullet_->render_b(bullet_);
				if (checkBulletCollision(bullet_)) {
					check_fire = 1;
					checkDam = true;
					bullet_list.erase(bullet_list.begin() + i);
					player_->setb_list(bullet_list);

					delete bullet_;
					bullet_ = NULL;
				}
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

void checkb_remain() {
	if (checkDam) {
		boss_health--;
		checkDam = false;
	}
	b_remain.str("");
	b_remain << boss_health;
	SDL_Color B_Health_Color = { 235, 51, 36 };
	if (!B_Health.loadFromText(b_remain.str().c_str(), "Images/lazy2.ttf", B_Health_Color, 30)) {
		cout << "Could not load Health text ! " << endl;
	}
	B_Health.render(900, 200);
}

void Guide() {
	while (guide_delay > 0) {
		GuideText.render(130, 450);
		SDL_RenderPresent(renderer);
		guide_delay--;
	}
}