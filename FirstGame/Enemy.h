#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class Enemy
{
private:

	//ไม่ใช้แม่งละ private

public:
	Enemy(const int id,int difficult);
	virtual ~Enemy();
	
	Vector2i window;
	Vector2i field;
	Vector2i fieldpos;

	RectangleShape shape;
	CircleShape cir_shape;

	float movementSpeed;
	Vector2f midposition;
	Vector2f position;
	int type;
	int id;
	FloatRect getglobal;

	float dirx, diry; //for track
	RectangleShape preshape; //for fatal type
	Clock dealtimer;
	int dealtimemax;


	void update();
	void render(RenderTarget& target);
};

