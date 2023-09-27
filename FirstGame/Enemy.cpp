#include "Enemy.h"
#include "Game.h"
using namespace sf;
Enemy::Enemy(const int id, int difficult)
{
	this->window = Vector2i(1920.f,1080.f);
	this->field = Vector2i(1700, 720);
	this->fieldpos = Vector2i(110, 250);

	this->type = 3;
	this->id = id;		//
	this->dirx = 0.f; //for tracking
	this->diry = 0.f;
	this->movementSpeed = 0.f;
	
	this->dealtimemax = 0;

	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(Color::Black);
	switch (id) {			//add enemy types here
	case 0:
		//straight downward enemy
			this->shape.setFillColor(Color::White);
			this->shape.setSize(Vector2f(30 , 30));
		if (difficult <= 1) {
			this->shape.setPosition(rand() % (field.x - 30) + fieldpos.x, 0);
			this->movementSpeed = 10.f;
		}
		if (difficult > 1) {
			int r = rand() % 2, x, y;
			if (r == 0) {
				x = rand() % (window.x - 30);
				y = (rand() % 2) * (window.y - 30);
			}
			else 
			{ 
				x = (rand() % 2) * (window.x - 30); 
				y = rand() % (window.y - 30);
			}
			this->shape.setPosition(x , y );
			this->movementSpeed = 15.f;
		}
		if (difficult > 2) {
			this->movementSpeed = 20.f;
		}
		this->position = this->shape.getPosition();
		break;
	case 1:
		//Fatal enemy
		this->preshape.setFillColor(Color(255, 255, 255,100));
		this->preshape.setSize(Vector2f(150.f, window.y));
		this->preshape.setPosition(rand() %  (field.x - 150) + fieldpos.x, 0);//  ,

		this->shape.setFillColor(Color::White);
		this->shape.setSize(this->preshape.getSize());
		this->shape.setPosition(window.x + 100, 0);

		this->dealtimemax = 2;
		if (difficult > 1) { this->dealtimemax = 1.5; }
		break;
	case 2:
		//tracking player enemy
		this->shape.setFillColor(Color::White);
		this->shape.setSize(Vector2f(10.f, 10.f));
		this->shape.setPosition(rand() % window.x, 0);
		this->movementSpeed = 5.f;

		this->dealtimemax = 6;
		break;
	case 3:
		//Side 
		break;
	case 4:		//bounce
		
		break;
	default:
		this->shape.setFillColor(Color::Red);
		this->shape.setSize(Vector2f(20.f,20.f));
		this->shape.setPosition(rand() % 780,0);
		this->position = this->shape.getPosition();
	}
	this->getglobal = this->shape.getGlobalBounds();	
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	this->position = this->shape.getPosition();
	this->midposition = Vector2f(this->position.x + this->shape.getSize().x, this->position.y + this->shape.getSize().y);
	this->getglobal = this->shape.getGlobalBounds();
}

void Enemy::render(RenderTarget& target)
{
	target.draw(this->preshape);
	target.draw(this->shape);
}

