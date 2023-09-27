#include "Game.h"
using namespace sf;
using namespace std;
 
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)

Game::Game() {		//กำหนดค่าเริ่มต้น
	this->initWindow();
	this->p_name = "Anonymous";
	this->initPlayer(p_name);
	this->initField();
	this->initFonts();
	this->initGUI();
	this->initGameStart();
	this->state = 0;

	this->isTypeName = false;

	if (!buffer.loadFromFile("8_bit.mp3"))
		std::cout << "\nERROR LOAD SOUND\n";
	if (!this->music.openFromFile("Sounds/Spider Dance.mp3"))
		std::cout << "\nERROR  TO  LOAD MUSIC\n";	
	this->music.play();
	this->music.setVolume(10.f);
	this->music.setLoop(1);

}

Game::~Game() {
	delete this->window;
	delete this->player;
}

void Game::initGameStart()
{
	life_time.restart(); 
	e_spawntime.restart();
	score_count.restart();
	e_rate.restart();
	pressed_delay = 0;
	initPlayer(p_name);
	this->mana = 5;
	this->max_mana = 5;
	this->score = 0;

	this->e_spawntime_max = 0.5f;
	this->e_type = 3;
	this->e_max = 10;
	this->track_max = 8;
	this->track_count = 0;
	this->fatal_max = 5;
	this->fatal_count = 0;

	this->i_spawntime_max = 4;
	this->i_max = 10;
	this->i_type = 3;

	this->tab_dir = 15;
	this->difficult = 0;

	this->is_hit = 0;
}

void Game::difficultAdjust()
{
	if (life_time.getElapsedTime().asSeconds() < 10) {
		this->e_type = 1;
	}
	else if (life_time.getElapsedTime().asSeconds() < 25) {
		this->e_type = 2;
	}
	else if (life_time.getElapsedTime().asSeconds() < 40) {
		this->e_type = 3;
	}
	else if (life_time.getElapsedTime().asSeconds() < 45) {
		this->difficult=1;
	}
	else if (life_time.getElapsedTime().asSeconds() < 80) {
		this->difficult=2;
	}
	else if (life_time.getElapsedTime().asSeconds() < 300) {
		this->difficult=3;
	}
	if (e_rate.getElapsedTime().asSeconds() >= 9) {
		this->e_max++;
		this->e_spawntime_max -= 0.05f;
		e_rate.restart();
	}
	if (e_spawntime_max < 0.05f) this->e_spawntime_max = 0.05f;
}

void Game::initPlayer(String name)	//เพิ่มobject player
{
	this->player = new Player(name);
	this->score = 0;
}

void Game::initField()	//Field
{
	this->fieldpos = Vector2i(110, 250);
	this->fieldsize = Vector2i(1700, 720);
	this->field.setSize(Vector2f(fieldsize));
	this->field.setPosition(Vector2f(fieldpos));
	this->field.setOutlineThickness(8);
	this->field.setOutlineColor(Color::White);
	this->field.setFillColor(Color::Black);
}

void Game::initFonts()	//font
{
	if (!this->Mitr_font.loadFromFile("Fonts/Mitr.ttf")) {
		std::cout << "ERROR FONT";
	}
	if (!this->Bit_font.loadFromFile("Fonts/Bitt.ttf")) {
		std::cout << "ERROR FONT";
	}
}

void Game::initTextFormat(Text* text ,const char str[]) //all text
{
	text->setFont(Mitr_font);
	text->setCharacterSize(50);
	text->setFillColor(Color::White);
	text->setString(str);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(1);
}

void Game::initButtonFormat(RectangleShape* button, Text text)
{
	button->setSize(text.getGlobalBounds().getSize() + Vector2f(40, 40));
	button->setPosition(text.getGlobalBounds().getPosition() - Vector2f(20, 20));
	button->setFillColor(Color::Transparent);
	button->setOutlineColor(Color::White);
	button->setOutlineThickness(5);
}

void Game::initGUI()
{
	this->initTextFormat(&playtext , "PLAY!");
	this->initTextFormat(&scoreboard_text, "SCOREBOARD");
	this->initTextFormat(&exittext, "EXIT");
	this->playtext.setPosition((windowwidth - this->playtext.getGlobalBounds().width) / 2, 350);
	this->scoreboard_text.setPosition((windowwidth - this->scoreboard_text.getGlobalBounds().width) / 2, 550);
	this->exittext.setPosition((windowwidth - this->exittext.getGlobalBounds().width) / 2, 740);
	this->initButtonFormat(&play_button, playtext);
	this->initButtonFormat(&score_button, scoreboard_text);
	this->initButtonFormat(&exit_button, exittext);

	this->initTextFormat(&hptext , "HP");
	this->hptext.setOutlineColor(Color::Black);
	this->hptext.setOutlineThickness(1);
	this->hptext.setPosition(fieldpos.x + (1700 - 846) / 2, fieldpos.y + fieldsize.y + 20); //846 from finding midposition with "length"

	this->initTextFormat(&gameover, "!-- GAME OVER --!");
	this->gameover.setPosition((windowwidth - this->gameover.getGlobalBounds().width) / 2, (windowheight - this->gameover.getGlobalBounds().height) / 2);

	this->initTextFormat(&next, "Back to Main Menu ->");
	this->next.setCharacterSize(30);
	this->next.setPosition((windowwidth - next.getGlobalBounds().width) / 2, (windowheight - next.getGlobalBounds().height) / 2 + 100);

	this->initTextFormat(&back2menu, "<- Back to Main Menu");
	this->back2menu.setCharacterSize(25);
	this->back2menu.setPosition(windowwidth - back2menu.getGlobalBounds().getSize().x - 20, 20);
	this->initTextFormat(&lifetimetext , NULL);

	this->initTextFormat(&hpcount, NULL);
	this->hpcount.setOutlineColor(Color::Black);
	this->hpcount.setOutlineThickness(1);
	this->hpbar.setOutlineColor(Color::Black);
	this->hpbar.setOutlineThickness(1);
	this->hpbar.setFillColor(Color::White);
	this->hpbar.setPosition(hptext.getPosition().x + hptext.getGlobalBounds().width + 20, hptext.getGlobalBounds().top);
	this->hpbar.setSize(Vector2f(600, hptext.getGlobalBounds().height)); 
	this->hpcount.setPosition(hpbar.getPosition().x + hpbar.getSize().x + 20, hptext.getPosition().y);

	this->hpbarback.setFillColor(Color::Transparent);
	this->hpbarback.setOutlineColor(Color::White);
	this->hpbarback.setOutlineThickness(2);
	this->hpbarback.setPosition(hpbar.getPosition() - Vector2f(3 , 3));
	this->hpbarback.setSize(hpbar.getSize() + Vector2f(6,6));

	this->back_button.setSize(back2menu.getGlobalBounds().getSize() + Vector2f(20,20));
	this->back_button.setPosition(back2menu.getPosition() - Vector2f(10 , 10));

	float gap = windowwidth - (fieldpos.x + fieldsize.x);
	this->mana_bar.setSize(Vector2f(fieldsize.y, 70));
	this->mana_bar.setFillColor(Color::Blue);
	this->mana_bar.setOrigin(mana_bar.getSize().x / 2, mana_bar.getSize().y/2);
	this->mana_bar.setPosition((fieldpos.x + fieldsize.x) + field.getOutlineThickness() + gap / 2, fieldpos.y + fieldsize.y / 2);
	this->mana_bar.setRotation(-90);
	this->mana_bar_back.setSize(mana_bar.getGlobalBounds().getSize() + Vector2f(6, 6));
	this->mana_bar_back.setPosition(mana_bar.getGlobalBounds().getPosition() - Vector2f(3.f,3.f));
	this->mana_bar_back.setFillColor(Color::Transparent);
	this->mana_bar_back.setOutlineThickness(2);
	this->mana_bar_back.setOutlineColor(Color::White);

	initTextFormat(&player_text, "PLAYER: ");
	this->player_text.setCharacterSize(35);
	this->player_text.setPosition(10, 10);

	this->initTextFormat(&p_name_text, "Anonymous");
	this->p_name_text.setCharacterSize(35);
	//this->player_name_text.setOrigin(player_name_text.getGlobalBounds().width() , 0.f);
	this->p_name_text.setPosition(player_text.getGlobalBounds().width + 20, 10);
	this->initButtonFormat(&name_button, p_name_text);
	name_button.setOutlineThickness(1);

	this->counter_tab.setOutlineThickness(1);
	this->counter_tab.setOutlineColor(Color::Black);
	this->counter_tab.setFillColor(Color::White);//สร้างบาร์ ขยับ

	initTextFormat(&title, "THE HERO");
	this->title.setCharacterSize(60);
	this->title.setOrigin(this->title.getGlobalBounds().getSize() / 2.f);
	this->title.setPosition(windowwidth / 2, 100);

	initTextFormat(&score_text,"SCORE: ");

	initTextFormat(&space, "SPACE BAR!");
	this->space.setOrigin(space.getGlobalBounds().getSize() / 2.f);
	this->space.setRotation(90);
	this->space.setPosition(windowwidth + 100, 0);

	initTextFormat(&music_text, "Music : ON");
	music_text.setCharacterSize(30);
	music_text.setPosition(windowwidth - 180, windowheight - 50);
	initButtonFormat(&music_toggle_button, music_text);
}

void Game::initWindow()	//window
{
	this->fps = 60;
	this->windowwidth = 1920;
	this->windowheight = 1080;
	this->window = new RenderWindow(VideoMode(windowwidth, windowheight), "The Hero", Style::Fullscreen | Style::Titlebar);
	this->window->setFramerateLimit(fps);
	this->window->setVerticalSyncEnabled(1);
}

//Functions
void Game::run()	//loop run
{	  //state 0 = menu , 1 = play , 2 = game over , 3 = scoreboard , 4 = counter
	while (this->window->isOpen()) {
		this->updatePollEvents();
		if (state == 1) {
			this->update(); //Normal
			this->render();
		}
		else if (state == 0) {
			this->menu();
		}
		else if (state == 2) {
			this->gameOverPage();
		}
		else if (state == 3) {
			this->scoreBoard();
		}
		else if (state == 4) {
			this->counterPhase();
		}
	}
}

void Game::update()	//update ทุกๆเฟรม
{
	this->updatePollEvents();
	this->updateInput();
	this->updateItems();
	this->scoreCountOnTime();

	this->player->update();
	if (is_hit > 0) {hitEffect(); }
	this->updateEnemies();
	this->Surprise();
	this->difficultAdjust();
	this->updateGUI();

	this->gameOver();
	this->exit2Menu();
}

void Game::updatePollEvents() //update หน้าต่างเกม
{
	Event e;
	//Close window
	while (this->window->pollEvent(e)) {
		if (e.Event::type == Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
			this->window->close();
		if (e.type == Event::TextEntered && isTypeName) {
			if (e.text.unicode == '\b' && p_name.getSize() > 0) { this->p_name.erase(p_name.getSize() - 1); }
			else if (e.text.unicode == '\b') { continue; }
			else {
				this->p_name += e.text.unicode;
			}
			if (p_name.getSize() > 10) { this->p_name.erase(p_name.getSize() - 1); }
		}
		if ( ( Keyboard::isKeyPressed(Keyboard::Enter) || Mouse::isButtonPressed(Mouse::Left) ) 
				&& isTypeName ) {
			this->isTypeName = false;
			if (p_name == "") { this->p_name = "Anonymous"; }
			initButtonFormat(&name_button, p_name_text);
		}
	}
	this->p_name_text.setString(p_name);
	initButtonFormat(&name_button, p_name_text);
}

void Game::menu() //menu interface
{
	this->updatePollEvents();
	if (isButtonPressed(play_button)) { this->initGameStart(); this->state = 1;}
	else if (isButtonPressed(score_button)) { this->state = 3;}
	else if (isButtonPressed(exit_button)) { this->window->close(); }
	else if (isButtonPressed(name_button)) {
		Clock delay;
		while(delay.getElapsedTime().asSeconds() < 0.2f){}
		this->p_name = "";
		this->isTypeName = true;
	}
	if (isButtonPressed(music_toggle_button) && life_time.getElapsedTime().asSeconds() > pressed_delay + 0.5f) {
		this->pressed_delay = life_time.getElapsedTime().asSeconds();
		if (music.getStatus() == Music::Playing) {
			this->music.stop();
			this->music_text.setString("Music : OFF");
		}
		else {
			this->music.play();
			this->music_text.setString("Music : ON");
		}
	}
	if(state != 0 && isTypeName == true){
		this->isTypeName = false;
		if (p_name == "") { this->p_name = "Anonymous"; }
		initButtonFormat(&name_button, p_name_text);
	}
	this->menuRender();
}

void Game::menuRender()
{
	this->window->clear(Color::Black);
	this->window->draw(this->player_text);
	this->window->draw(this->playtext);
	this->window->draw(this->play_button);
	this->window->draw(this->scoreboard_text);
	this->window->draw(this->score_button);
	this->window->draw(this->exittext);
	this->window->draw(this->exit_button);
	this->window->draw(this->title);
	this->window->draw(this->p_name_text);
	this->window->draw(this->music_text);
	this->window->display();
}

void Game::scoreBoard()
{
	this->updatePollEvents();
	if (isButtonPressed(back_button)) {
		this->state = 0;
		Clock s;
		while(s.getElapsedTime().asMilliseconds()<200){}
	}
	score_i.open("Leaderboard.txt", ios::in);
	char N[10], i = 0;
	int t, s;
	stringstream n, tm, sc;
	while (score_i >> N >> t >> s) {
		n << N << "\n";
		tm << t << "\n";
		sc << s << "\n";
	}
	score_i.close();

	Text num, topic, name, time, Score;
	initTextFormat(&topic, "Name        |   Time(s.)   |   Score");
	initTextFormat(&num, "1.\n2.\n3.\n4.\n5.");
	initTextFormat(&name, n.str().c_str());
	initTextFormat(&time, tm.str().c_str());
	initTextFormat(&Score, sc.str().c_str());
	topic.setPosition(windowwidth / 2 - topic.getGlobalBounds().getSize().x/2, 250);
	num.setPosition(topic.getPosition() + Vector2f(-150, 100));
	name.setPosition(num.getPosition() + Vector2f(70, 0));
	time.setPosition(name.getPosition() + Vector2f(475, 0));
	Score.setPosition(time.getPosition() + Vector2f(300, 0));

	this->window->clear();
	window->draw(back2menu);
	window->draw(topic);
	window->draw(num);
	window->draw(name);
	window->draw(time);
	window->draw(Score);
	this->window->display();
}

void Game::counterPhase()
{
	window->clear(Color::Black);
	window->draw(field);
	this->exit2Menu();

	if (clock.getElapsedTime().asSeconds() <= 0.7) {
		this->field.setSize(field.getSize() - Vector2f(10.f, 12.f));
		this->field.setPosition(field.getPosition() + Vector2f(5.f, 5.5f));
		this->field.setOutlineThickness(4);
	}
	else if(clock.getElapsedTime().asSeconds() <= 0.8f){
		this->counter_tab.setSize(Vector2f(40, field.getSize().y) - Vector2f(2, 2));
		this->counter_tab.setOrigin(counter_tab.getSize() / 2.f);
		this->counter_tab.setPosition(field.getPosition() + Vector2f(counter_tab.getOrigin().x + 1, field.getSize().y / 2));

		this->indicator[0] = sf::Vertex(field.getPosition(),														sf::Color::Blue) ;
		this->indicator[1] = sf::Vertex(field.getPosition() + Vector2f(field.getSize().x / 2 , 0),					sf::Color::Red);
		this->indicator[2] = sf::Vertex(field.getPosition() + Vector2f(field.getSize().x / 2 , field.getSize().y),	sf::Color::Red);
		this->indicator[3] = sf::Vertex(field.getPosition() + Vector2f(0 , field.getSize().y),						sf::Color::Blue);
		this->indicator[4] = sf::Vertex(field.getPosition() + Vector2f(field.getSize().x / 2 , 0),					sf::Color::Red) ;
		this->indicator[5] = sf::Vertex(field.getPosition() + Vector2f(field.getSize().x, 0),						sf::Color::Blue) ;
		this->indicator[6] = sf::Vertex(field.getPosition() + field.getSize(),										sf::Color::Blue) ;
		this->indicator[7] = sf::Vertex(field.getPosition() + Vector2f(field.getSize().x / 2 , field.getSize().y),	sf::Color::Red);
		//สร้างbar
		//เคลื่อนbar
	}
	else {
		window->draw(indicator, 8, Quads);
		this->window->draw(counter_tab);
		panya();
	}
	if(Keyboard::isKeyPressed(Keyboard::Space)){
		mana -= 5;
		state = 1;
		checkAcc();
		initField();
	}
	
	window->draw(mana_bar);
	window->draw(mana_bar_back);
	this->window->draw(back2menu);
	window->display();
}

int Game::isButtonPressed(RectangleShape button) //check "play" button pressed
{
	Vector2i m = Mouse::getPosition(*this->window);
	Vector2f mouse = this->window->mapPixelToCoords(m);
	if (Mouse::isButtonPressed(Mouse::Left) && button.getGlobalBounds().contains(mouse)) {
		return 1;
	}
	return 0;
}
	
void Game::updateGUI() //update GUI
{
	this->hpbar.setSize(Vector2f((hpbarback.getSize().x - 6) * player->hp / player->maxhp, hpbar.getSize().y)); //dynamic hpbar
	stringstream hp , time;
	hp << player->hp << "/" << player->maxhp;
	this->hpcount.setString(hp.str());

	time << int(life_time.getElapsedTime().asSeconds());
	this->lifetimetext.setString(time.str());
	this->lifetimetext.setOrigin(lifetimetext.getGlobalBounds().getSize().x / 2 , 0);
	this->lifetimetext.setPosition(windowwidth/2.0f , 0);

	this->mana_bar.setSize(Vector2f((mana_bar_back.getGlobalBounds().getSize().y - 6) * mana / max_mana, mana_bar.getSize().y)); //dynamic chargebar
	if (mana >= max_mana) {
		space.setPosition(mana_bar_back.getGlobalBounds().getPosition() + mana_bar_back.getGlobalBounds().getSize() / 2.f + Vector2f(10,0));
	}

	//score
	stringstream score;
	score << "SCORE: " << this->score;
	this->score_text.setString(score.str());
}

void Game::scoreCountOnTime()
{
	if (score_count.getElapsedTime().asSeconds() > 5) {
		score_count.restart();
		this->score += 5;
	}
}

void Game::updateInput()	//update input to control player
{
	float x = 0, y = 0;
	//move player
	if (Keyboard::isKeyPressed(Keyboard::A))
		x -= 1.f;
	if (Keyboard::isKeyPressed(Keyboard::D))
		x +=  1.f;
	if (Keyboard::isKeyPressed(Keyboard::W))
		y -= 1.f;
	if (Keyboard::isKeyPressed(Keyboard::S))
		y += 1.f;
	this->player->move(x, y);
	if (Keyboard::isKeyPressed(Keyboard::Space) && mana >= max_mana) {
		score += enemies.size() * 10;
		enemies.clear();	
		mana -= max_mana;
	}
}

void Game::spawnEnemies()	//spawn enemy เพิ่มไว้ในVector ไม่เกิน enemyMax
{
	if (e_spawntime.getElapsedTime().asSeconds() > e_spawntime_max && this->enemies.size() < this->e_max) {
		int id = rand() % e_type;
		while ((id == 2 && track_count >= track_max) || (id == 1 && fatal_count >= fatal_max))id = rand() % e_type;
		this->enemies.push_back(new Enemy(id,difficult));
		this->e_spawntime.restart();
		int i = enemies.size() - 1;
		if (id == 0) {
			Vector2f p = player->shape.getGlobalBounds().getPosition();
			Vector2f e = enemies[i]->shape.getGlobalBounds().getPosition();
			float d = sqrt(float(pow(p.x-e.x , 2) + pow(p.y - e.y , 2)));
			this->enemies[i]->dirx = (p.x - e.x) / d;
			this->enemies[i]->diry = (p.y - e.y) / d;
		}
	}
}

void Game::updateEnemies()	//update enemy ทุกตัว ทุกการกระทำ
{
	// เรียกspawn enemy
	spawnEnemies();
	int i = 0;
	int e_type_count[5] = {0};
	for (i = 0;i < enemies.size();i++) {
		int id = enemies[i]->id;
		e_type_count[id]++;
		enemyAttack(i);
		enemyDelete(i);
	}
	track_count = e_type_count[2];
	fatal_count = e_type_count[1];
}

void Game::enemyAttack(int i)	//how enemy attack by each type
{
	switch (this->enemies[i]->id) {
		case 0:				//straight downward
			this->aimMove(i);
			break;
		case 1:				
			this->fatalMove(i);
			break;
		case 2:
			this->trackMove(i);
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			this->enemies[i]->shape.move(0.f, 0.f);
		}
	this->enemies[i]->update();
}

void Game::trackMove(const int i)	
{
	Enemy* enemy = this->enemies[i];
	float accel = 0.08f;
	if (enemy->midposition.x < this->player->midposition.x) enemy->dirx += accel;
	if (enemy->midposition.x > this->player->midposition.x) enemy->dirx -= accel;
	if (enemy->midposition.y < this->player->midposition.y) enemy->diry += accel;
	if (enemy->midposition.y > this->player->midposition.y) enemy->diry -= accel;
	
	if (enemy->dirx > 1) enemy->dirx-= accel;
	if (enemy->diry > 1) enemy->diry-= accel;
	if (enemy->dirx < -1) enemy->dirx+= accel;
	if (enemy->diry < -1) enemy->diry+= accel;
	enemy->shape.move(enemy->movementSpeed * enemy->dirx, enemy->movementSpeed * enemy->diry);
}

void Game::fatalMove(const int i)
{
	if (this->enemies[i]->dealtimer.getElapsedTime().asSeconds() >= this->enemies[i]->dealtimemax) {
		this->enemies[i]->dealtimer.restart();
		this->enemies[i]->shape.setPosition(this->enemies[i]->preshape.getPosition());
		this->enemies[i]->getglobal = enemies[i]->shape.getGlobalBounds();
	}
}

void Game::aimMove(const int i)
{
	this->enemies[i]->shape.move(enemies[i]->movementSpeed * enemies[i]->dirx, enemies[i]->movementSpeed * enemies[i]->diry);

}

void Game::spawnItems()
{
	if (this->i_spawntime.getElapsedTime().asSeconds() >= this->i_spawntime_max && this->items.size() < this->i_max) {

		this->items.push_back(new Item());
		this->i_spawntime.restart();
	}
}

void Game::collectItems(int i)
{
	if (isHit(this->player->getglobal, this->items[i]->shape.getGlobalBounds())) {
		score += 5;
		if (items[i]->id == 0) {
			mana += 1;
			is_hit = 2;
		}
		else if (items[i]->id == 1) {
			this->player->hp++;
			is_hit = 3;
		}
		else if (items[i]->id == 2) {
			is_hit = 4;
			this->Surprise();
		}
		this->items.erase(this->items.begin() + i);
		this->clock.restart();
	}
	if (mana > max_mana) { mana = max_mana; }
	if (player->hp > player->maxhp) { player->hp = player->maxhp; }
}

void Game::updateItems()
{
	spawnItems();
	for (int i = 0;i < items.size();i++) {
		this->items[i]->shape.setRotation(this->items[i]->shape.getRotation() + 1);
		collectItems(i);
	}
	/*this->b.setOutlineThickness(1);
	this->b.setOutlineColor(Color::White);
	this->b.setFillColor(Color::Transparent);
	this->b.setSize(item->shape.getGlobalBounds().getSize());
	this->b.setPosition(item->shape.getGlobalBounds().getPosition());*/
}

void Game::enemyDelete(int i) //what way enemy deleted
{
	int dmg = 0;
	if (this->isHitPlayer(i)) {   //deal dmg
		dmg = 1;
		this->enemies.erase(this->enemies.begin() + i);
	}
	else if(this->enemies[i]->id == 0 && this->isOutWindow(i)){  //id 0
		this->enemies.erase(this->enemies.begin() + i);
	}
	else if (this->enemies[i]->shape.getPosition() == this->enemies[i]->preshape.getPosition() && this->enemies[i]->dealtimer.getElapsedTime().asSeconds() > 0.5) { //fatal auto del
		this->enemies.erase(this->enemies.begin() + i);
	}else if(enemies[i]->dealtimer.getElapsedTime().asSeconds() >= enemies[i]->dealtimemax && enemies[i]->id == 2) { //track auto del
		this->enemies.erase(this->enemies.begin() + i);
	}
	this->player->hp -= dmg;	
}

bool Game::isOutWindow(int i)	//check if enemy out of field's bottom or not
{
	if (enemies[i]->getglobal.top + enemies[i]->getglobal.height > windowheight+50 && enemies[i]->diry > 0) return 1;
	if (enemies[i]->getglobal.left < -50 && enemies[i]->dirx < 0) return 1;
	if (enemies[i]->getglobal.left + enemies[i]->getglobal.width > windowwidth+50 && enemies[i]->dirx > 0) return 1;
	if (enemies[i]->getglobal.top < -50 && enemies[i]->diry < 0) return 1;
	return 0;
}

bool Game::isHitPlayer(int i)	//check if enemy hit player
{
	bool r = false;
	if (this->enemies[i]->getglobal.intersects(this->player->getglobal)) {
		r = true;
	}
	else if (this->player->getglobal.intersects(this->enemies[i]->getglobal)) {
		r = true;
	}
	if (r == true) {
		is_hit = 1;
		this->clock.restart();
	}

	return r;
}

bool Game::isPlayerDead()
{
	if (this->player->hp <= 0) return true;
	return false;
}

bool Game::isHit(FloatRect a, FloatRect b)
{
	if (a.intersects(b)) {
		return 1;
	}
	else if (b.intersects(a)) {
		return 1;
	}
	return 0;
}

bool Game::isPause()
{

	return false;
}

void Game::checkAcc()
{
	float tabpos = counter_tab.getPosition().x - field.getPosition().x; 
	float length = field.getSize().x;
	float tmp = abs(tabpos - length / 2) - (length/2);   //665 - 645  
	tmp = abs(tmp);
	tmp = tmp / (length / 2);
	tmp *= 100;
	this->score += tmp;
}

void Game::Surprise()
{
	
}

void Game::hitEffect()
{
	if (clock.getElapsedTime().asSeconds() < 0.2f && is_hit>0) {
		if (is_hit == 1) {
			this->player->shape.setOutlineColor(Color::White);
		}
		else if (is_hit == 2) {
			this->player->shape.setOutlineColor(Color::Blue);
		}
		else if (is_hit == 3) {
			this->player->shape.setOutlineColor(Color::Green);
		}else if(is_hit == 4){
			this->player->shape.setOutlineColor(Color::Yellow);
		}
	}
	else{
		this->player->shape.setFillColor(Color::Red);
		this->player->shape.setOutlineColor(Color::Black);

		this->clock.restart();
		this->is_hit = 0;
	}

}

void Game::insertName()
{
	bool close = false;
	while (!Keyboard::isKeyPressed(Keyboard::Enter)) {
		Event t;
		while (window->pollEvent(t)) {
			if (t.Event::key.code == Keyboard::Escape || t.type == Event::Closed) {
				this->window->close();
				close = true;
				break;
			}
			if (t.type == Event::TextEntered) {
				if (t.text.unicode == '\b' && p_name.getSize()>0) { this->p_name.erase(p_name.getSize()-1) ; }
				else {
					this->p_name += t.text.unicode;
				}
				if (p_name.getSize() > 10) { this->p_name.erase(p_name.getSize() - 1); }
			}
		}
		if (close == true) break;
		this->p_name_text.setString(p_name);
	}
}

void Game::exit2Menu()
{
	if (isButtonPressed(back_button)) {
		this->resetGame();
	}
}

void Game::gameOver()
{
	if (this->isPlayerDead() == 1) {
		state = 2;
		over_timer.restart();
		scoreLog();
	}
}

void Game::gameOverPage()
{
	this->window->clear(Color::Black);

	this->updatePollEvents();
	if (this->over_timer.getElapsedTime().asSeconds() > 2 ) {
		Vector2i m = Mouse::getPosition(*this->window);
		Vector2f mouse = this->window->mapPixelToCoords(m);
		if (Mouse::isButtonPressed(Mouse::Left) && this->next.getGlobalBounds().contains(mouse)) {
			this->resetGame();
		}
		this->window->draw(this->next);
	}
	this->window->draw(this->gameover);

	this->window->display();
}

void Game::resetGame()
{
	this->enemies.clear();
	this->items.clear();
	this->e_spawntime.restart();
	this->state = 0;
	this->initField();
	this->life_time.restart();
	while(life_time.getElapsedTime().asSeconds() < 0.4f){}
}

void Game::scoreLog()
{
	score_i.open("LeaderBoard.txt",ios::in);
	int time, sc;
	char name[10];
	vector<int> Time, Sc;
	char Name[5][10];
	//name time score
	int i = 0;
	while (score_i >> name >> time >> sc) {
		Time.push_back(time);
		Sc.push_back(sc);
		strcpy_s(Name[i], name);
		cout << Name[i] <<Time[i] << Sc[i] << "\n";
		i++;
	}
	//เรียงอันดับ
	score_i.close();
	score_o.open("LeaderBoard.txt", ios::out);
	stringstream n;
	int count = 0;
	n.str(p_name);
	for (int j = 0;j < i && count <5;j++) {
		if (score > Sc[j]) {
			score_o << n.str() << " " << int(life_time.getElapsedTime().asSeconds()) << " " << score << "\n";
			this->score = -1;
			count++,j--;
			continue;
		}
		score_o << Name[j] << " " << Time[j] << " " << Sc[j] << "\n";
		count++;
	}
	if (score != -1 && count<5) {
		score_o << n.str() << " " << int(life_time.getElapsedTime().asSeconds()) << " " << score << "\n";
		this->score = -1;
	}
	score_o.close();
}

void Game::scoreRead()
{

}

void Game::panya()
{
	this->counter_tab.move(tab_dir, 0);
	if (counter_tab.getGlobalBounds().getPosition().x + counter_tab.getGlobalBounds().getSize().x >= field.getPosition().x + field.getSize().x) this->tab_dir = -tab_dir;
	if (counter_tab.getGlobalBounds().getPosition().x  < field.getPosition().x) this->tab_dir = -tab_dir;
}

void Game::renderGUI()
{
	this->window->draw(hptext);
	this->window->draw(hpbar);
	this->window->draw(hpbarback);
	this->window->draw(hpcount);
	this->window->draw(back2menu);
	this->window->draw(lifetimetext);
	this->window->draw(mana_bar);
	this->window->draw(mana_bar_back);
	this->window->draw(score_text);
	if (mana == max_mana) {
		this->window->draw(space);
	}
}

void Game::render()				//render
{
	this->window->clear(Color::Black); 
	window->draw(this->field);	//field	

	window->draw(b);

	for (auto& e : this->items) {
		this->window->draw(e->shape);
	}

	for (auto& e : this->enemies) {		//enemy
		e->render(*this->window);
	}
	this->renderGUI();	//GUI
	this->player->render(*this->window); //player
	this->window->display();			//แสดงผล
}
;
