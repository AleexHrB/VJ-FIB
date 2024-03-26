#include "Bubble.h"
#include<iostream>

void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Color c, Size s, const glm::vec2& initPos, const glm::vec2& speed)
{
	spritesheet.loadFromFile("images/Bubble.png", TEXTURE_PIXEL_FORMAT_RGBA);
	const glm::ivec2 bigSize = glm::ivec2(80, 80);
	sizeQuad = bigSize / (1 << s);
	this -> s = s;
	this->c = c;
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0/4.0, 1.0 / 3.0), &spritesheet, &shaderProgram);
	this->speed = speed;
	this->position = this-> initPosBubble = initPos;
	sprite->setPosition(glm::vec2(float(position.x), float(position.y)));
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0, c / 3.0));
	sprite->changeAnimation(0);

	sprite->setAnimationSpeed(1, 8);
	sprite->loopAnimation(1, false);
	sprite->addKeyframe(1, glm::vec2(1 /4.0, c / 3.0));
	sprite->addKeyframe(1, glm::vec2(2 / 4.0, c / 3.0));
	sprite->addKeyframe(1, glm::vec2(3 / 4.0, c / 3.0));
}

void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
}

void Bubble::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (!destroying) {
		t += deltaTime / 100.0;
		position.x = initPosBubble.x + speed.x * t;
		position.y = initPosBubble.y + speed.y * t + 0.5 * g * t * t;


		if (map->collisionMoveDown(position, sizeQuad, &position.y)) {
			t -= 2 * deltaTime / 100.0;
			position.x = initPosBubble.x + speed.x * t;
			position.y = initPosBubble.y + speed.y * t + 0.5 * g * t * t;
			initPosBubble = position;
			speed.y += g * t;
			speed.y *= -1;
			t = 0.1;
		}

		else if (map->collisionMoveUp(position, sizeQuad, &position.y)) {
			t -= 2 * deltaTime / 100.0;
			position.x = initPosBubble.x + speed.x * t;
			position.y = initPosBubble.y + speed.y * t + 0.5 * g * t * t;
			initPosBubble = position;
			speed.y += g * t;
			speed.y *= -1;
			t = 0.1;
		}

		if (map->collisionMoveRight(position, sizeQuad))
		{
			t -= 2 * deltaTime / 100.0;
			position.x = initPosBubble.x + speed.x * t;
			position.y = initPosBubble.y + speed.y * t + 0.5 * g * t * t;
			initPosBubble = position;
			speed.y += g * t;
			speed.x *= -1;
			t = 0.1;
		}
		else if (map->collisionMoveLeft(position, sizeQuad)) {
			t -= 2 * deltaTime / 100.0;
			position.x = initPosBubble.x + speed.x * t;
			position.y = initPosBubble.y + speed.y * t + 0.5 * g * t * t;
			initPosBubble = position;
			speed.y += g * t;
			speed.x *= -1;
			t = 0.1;
		}

		sprite->setPosition(glm::vec2(float(position.x), float(position.y)));
	}
	else if (sprite->animation() == 0) destroyed = true;
}

//Source: https://algo.monster/liteproblems/1401
bool Bubble::checkCollision(const pair<glm::ivec2, glm::ivec2>& hitbox)
{
	pair<glm::ivec2, glm::ivec2> c = getHitbox();
	unsigned int deltaX = getMinimumDistance(hitbox.second.x, hitbox.second.x + hitbox.first.x, (c.second + c.first / 2).x);
	unsigned int deltaY = getMinimumDistance(hitbox.second.y, hitbox.second.y + hitbox.first.y, (c.second + c.first / 2).y);

	return deltaX * deltaX + deltaY * deltaY <= c.first.x * c.first.x / 4;
}

void Bubble::changeGravity(float g)
{
	this->g = g;
}

unsigned int Bubble::getBonus()
{
	switch (this->s) {
	case Size::BIG:
		return 50;
	case Size::MID:
		return 100;
	case Size::SMALL:
		return 150;
	case Size::TINY:
		return 200;
	default:
		return 0;
	}
}

bool Bubble::isDestroying()
{
	return destroying;
}

bool Bubble::isDestroyed()
{
	return destroyed;
}



void Bubble::destroy()
{
	destroying = true;
	sprite->setNextAnimation(0);
	sprite->changeAnimation(1);
}


Bubble::Size Bubble::getSize()
{
	return this -> s;
}

Bubble::Color Bubble::getColor()
{
	return this -> c;
}
