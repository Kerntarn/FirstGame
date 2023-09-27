#include "Item.h"

Item::Item()
{
	this->window = Vector2i(1920.f, 1080.f);
	this->field = Vector2i(1700, 720);
	this->fieldpos = Vector2i(110, 250);

	this->initShape();
	this->id = rand() % 100;
	if (id < 53) { this->id = 0; }
	else if (id < 98) { this->id = 1; }
	else {this->id = 2;}
	switch (id) {
		case 0:
			this->shape.setFillColor(Color::Blue);
			break;
		case 1:
			this->shape.setFillColor(Color::Green);
			break;
		case 2:
			this->shape.setFillColor(Color::Yellow);
			break;
	}

}

Item::~Item()
{
}

void Item::initShape()
{
	this->shape.setSize(Vector2f(20,20));
	this->shape.setFillColor(Color::Blue);
	this->shape.setOrigin(7.5, 7.5);
	this->shape.setPosition(rand() % field.x + fieldpos.x, rand() % field.y + fieldpos.y);
}
