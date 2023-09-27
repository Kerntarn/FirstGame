#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Player
{
private:

	Vector2i window;
	Vector2i field;
	Vector2i fieldpos;

public:
	Player(String name);
	virtual ~Player();

	Sprite sprite;
	Texture texture;

	//Variables
	float movementSpeed;
	Vector2f curspeed;
	RectangleShape shape;
	RectangleShape back_shape;

	//Private Functions
	void initSprite();
	void initTexture();
	void initShape();

	//Functions
	void move(const float dirx, const float diry); 
	void updateCollision();
	float dashspeed;
	int dashcd;
	int dashtime;

	int hp;
	int maxhp;

	void counter(int time);
	int countertime;

	Vector2f position;
	Vector2f midposition;
	FloatRect getglobal;

	void update();
	void render(RenderTarget& target);


};

