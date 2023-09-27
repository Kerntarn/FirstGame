#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class Item
{
private:

public:
	Item();
	virtual ~Item();
	Vector2i window;
	Vector2i field;
	Vector2i fieldpos;

	void initShape();
	RectangleShape shape;

	int id;
};

