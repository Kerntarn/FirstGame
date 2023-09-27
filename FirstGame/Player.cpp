#include "Player.h"
using namespace sf;


//Private Functions
void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(3.f, 3.f);
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/BetaTester.png")) {
		std::cout << "Can't Load Texturewa boi.\n";
	}
}

void Player::initShape()
{
	this->shape.setFillColor(Color::Red);
	this->shape.setSize(Vector2f(20.f, 20.f));
	this->shape.setPosition(Vector2f(fieldpos) + Vector2f(field / 2) - Vector2f(shape.getSize() / 2.f) );
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(Color::Black);
	
}

Player::Player(String name)
{
	this->window = Vector2i(1920.f, 1080.f);
	this->field = Vector2i(1700, 720);
	this->fieldpos = Vector2i(110, 250);

	this->movementSpeed = 6.f;
	this->initShape();
	this->position = this->shape.getPosition();
	this->getglobal = this->shape.getGlobalBounds();
	this->midposition = Vector2f((this->position.x + this->getglobal.width / 2),(this->position.y + this->getglobal.height / 2));
	this->dashspeed = 200;
	this->dashcd = 120;
	this->dashtime = 0;

	this->maxhp = 10;
	this->hp = maxhp;

	this->curspeed = Vector2f(0, 0);

	this->countertime = 0;
	//this->initTexture();
	//this->initSprite();
}

Player::~Player()
{

}

void Player::move(const float dirX, const float dirY) //dynamic move
{
	/*if (dirX == 0 && curspeed.x != 0) {
		curspeed.x < 0 ? this->curspeed.x += 1 : this->curspeed.x -= 1;
	}
	if (dirY == 0 && curspeed.y != 0){
		curspeed.y < 0 ? this->curspeed.y += 1 : this->curspeed.y -= 1;
	}
	this->curspeed.x += dirX;
	this->curspeed.y += dirY;
	if (curspeed.x > movementSpeed) this->curspeed.x -= dirX;
	if (curspeed.y > movementSpeed) this->curspeed.y -= dirY;
	if (curspeed.x < -movementSpeed) this->curspeed.x -= dirX;
	if (curspeed.y < -movementSpeed) this->curspeed.y -= dirY;
	this->shape.move(curspeed.x, curspeed.y);*/
	this->shape.move(dirX * movementSpeed, dirY * movementSpeed);
}

void Player::updateCollision()
{
	if (this->shape.getGlobalBounds().getPosition().y < fieldpos.y) this->shape.move( 0 , fieldpos.y - shape.getGlobalBounds().getPosition().y);   //top
	if (this->shape.getGlobalBounds().getPosition().x < fieldpos.x) this->shape.move(fieldpos.x - shape.getGlobalBounds().getPosition().x , 0);	//left
	if (this->shape.getGlobalBounds().getPosition().y + shape.getGlobalBounds().getSize().y > fieldpos.y + field.y) this->shape.move(0, fieldpos.y + field.y - (shape.getGlobalBounds().getPosition().y + shape.getGlobalBounds().getSize().y) ); //bottom
	if (this->shape.getGlobalBounds().getPosition().x + shape.getGlobalBounds().getSize().x > fieldpos.x + field.x) this->shape.move(fieldpos.x + field.x - (shape.getGlobalBounds().getPosition().x + shape.getGlobalBounds().getSize().x), 0 ); //right
}

void Player::counter(int time)
{
	if (time != 0) {
		this->shape.setFillColor(Color::Blue);
		this->countertime--;
	}
	else {
		this->shape.setFillColor(Color::Red);
	}
}

//Functions
void Player::update()	//update state
{
	this->updateCollision();
	this->counter(this->countertime);
	this->position = this->shape.getGlobalBounds().getPosition();
	this->getglobal = this->shape.getGlobalBounds();
	this->midposition = Vector2f((this->position.x + this->getglobal.width / 2), (this->position.y + this->getglobal.height / 2));
	this->dashtime++;
}

void Player::render(RenderTarget& target)
{
	target.draw(this->shape);

}

