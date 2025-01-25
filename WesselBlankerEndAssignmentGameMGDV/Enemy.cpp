#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow& window)
{
	this->initShape(window);
	this->initVariables();
}

Enemy::~Enemy()
{

}

void Enemy::initVariables()
{
	this->hitBottom = false;

	float velX = static_cast<float>(rand() % (2 * 200 + 1) - 200) / 100;
	float velY = static_cast<float>(rand() % 100 + 75) / 100;
	this->velocity = sf::Vector2f(velX, velY);
}

void Enemy::initShape(sf::RenderWindow& window)
{
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color(255,50,50));
	this->shape.setOutlineThickness(-2.f);
	this->shape.setRadius(static_cast<float>(rand() % 16 + 45));

	float shapePosX = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
	float shapePosY = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);

	if (shapePosX < 0.f) {
		shapePosX = 0.f;
	}

	shapePosY = -this->shape.getGlobalBounds().height;
	this->shape.setPosition(sf::Vector2f(shapePosX, shapePosY));
}

const sf::CircleShape Enemy::getShape() const
{
	return this->shape;
}

const bool Enemy::getHitBottom() const
{
	return this->hitBottom;
}

void Enemy::updateMovement()
{
	this->shape.move(velocity.x, velocity.y);
}

void Enemy::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left
	if (this->shape.getGlobalBounds().left <= 0.f) 
	{
		this->velocity.x *= -1;
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}
	// Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x) 
	{
		this->velocity.x *= -1;
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}
	// Top
	if (this->shape.getGlobalBounds().top <= -this->shape.getGlobalBounds().height)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, -this->shape.getGlobalBounds().height);
	}
	// Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y + this->shape.getGlobalBounds().height)
	{
		this->hitBottom = true;
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y + this->shape.getGlobalBounds().height);
	}
}

void Enemy::update(const sf::RenderTarget* target)
{
	//Movement Update
	updateMovement();

	//Window Bounds Collision
	updateWindowBoundsCollision(target);
}



void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}