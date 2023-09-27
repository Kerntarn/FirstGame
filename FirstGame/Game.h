#pragma once
#include<map>
#include<sstream>
#include"Player.h"
#include"Enemy.h"
#include"Item.h"
#include <fstream>

using namespace sf;
using namespace std;
class Game
{
private:
	//Variables

	int windowheight;
	int windowwidth;
	
	//Resources

	//Player
	Player* player;

	//Enemy
	int track_max;
	int track_count;
	int fatal_max;
	int fatal_count;
	//Window
	RenderWindow* window;
	int fps;

	//Private Functions
	void initWindow();
	void initPlayer(String name);
	void initField();
	void initFonts();
	void initTextFormat(Text* text,const char str[]);
	void initButtonFormat(RectangleShape* button, Text text);
	void initGUI();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();
	void updatePollEvents();
	void menu();
	void menuRender();
	void scoreBoard();
	void counterPhase();
	int isButtonPressed(RectangleShape button);
	int state;

	String p_name;
	Text p_name_text;
	void insertName();
	bool isTypeName;

	void exit2Menu();
	void gameOver();
	void gameOverPage();
	void resetGame();
	void initGameStart();
	Clock over_timer;
	Clock clock;
	int score;
	int time_score;
	int difficult;
	void scoreLog();
	void scoreRead();
	ofstream score_o;
	ifstream score_i;
	FILE* fp;

	Clock life_time;
	Clock e_rate;
	Text lifetimetext;
	int mana;
	int max_mana;
	RectangleShape	mana_bar;
	RectangleShape mana_bar_back;
	Vertex indicator[8];
	void panya();
	RectangleShape counter_tab;
	int tab_dir;

	Font Mitr_font;
	Font Bit_font;
	Text playtext;
	Text scoreboard_text;
	Text exittext;
	String input;
	Text player_text;
	Text title;
	Text space;

	Text hptext;
	Text hpcount;
	Text score_text;
	Text gameover;
	Text next;
	Text back2menu;
	RectangleShape exit_button;
	RectangleShape back_button;
	RectangleShape play_button;
	RectangleShape score_button;
	RectangleShape name_button;
	RectangleShape hpbar;
	RectangleShape hpbarback;
	void updateGUI();
	void scoreCountOnTime();
	Clock score_count;

	void updateInput();	
	Vector2i mousepos;

	RectangleShape field;
	Vector2i fieldsize;
	Vector2i fieldpos;

	std::vector<Enemy*> enemies;
	int e_type;
	int e_max;
	void difficultAdjust();
	Clock e_spawntime;
	float e_spawntime_max;
	void spawnEnemies();
	void updateEnemies();
	void enemyAttack(int i);
	void enemyDelete(int i);
	void trackMove(const int i);
	void fatalMove(const int i);
	void aimMove(const int i);

	std::vector<Item*> items;
	void spawnItems();
	Clock i_spawntime;
	int i_spawntime_max;
	int i_max;
	int i_type;
	void collectItems(int i);
	void updateItems();
	RectangleShape b;

	bool isOutWindow(int i);
	bool isHitPlayer(int i);
	bool isPlayerDead();
	bool isHit(FloatRect a, FloatRect b);
	bool isPause();

	void checkAcc();
	void Surprise();
	void hitEffect();
	int is_hit;
	SoundBuffer buffer;
	Sound sound;
	Music music;
	Text music_text;
	RectangleShape music_toggle_button;
	float pressed_delay;

	void update();
	void renderGUI();
	void render();
};

