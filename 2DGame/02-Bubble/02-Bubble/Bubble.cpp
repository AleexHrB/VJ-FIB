#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Bubble.h"
#include "Game.h"


void Bubble::init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size, unsigned int color)
{
	
	spritesheet.loadFromFile("images/Bubbles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = size;
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0, 1.0/3.0), &spritesheet, &shaderProgram);
	this->speed = speed;
	this->posBubble = this->initposBubble = initPos;
	sprite->setPosition(glm::vec2(float(posBubble.x), float(posBubble.y)));
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0, color / 3.0));
	sprite->changeAnimation(0);
}

void Bubble::update(int deltaTime)
{
	sprite->update(deltaTime);
	t += deltaTime / 100.0;
	posBubble.x = initposBubble.x + speed.x * t;
	posBubble.y = initposBubble.y + speed.y * t + 0.5 * g * t * t;

	if (map->collisionMoveDown(posBubble, sizeQuad, &posBubble.y)) {
		t -= 2*deltaTime / 100.0;
		posBubble.x = initposBubble.x + speed.x * t;
		posBubble.y = initposBubble.y + speed.y * t + 0.5 * g * t * t;
		initposBubble = posBubble;
		speed.y += g*t;
		speed.y *= -1;
		t = 0.1;
	}
	
	if (map->collisionMoveLeft(posBubble, sizeQuad) || map->collisionMoveRight(posBubble, sizeQuad))
	{
		t -= 2*deltaTime / 100.0;
		posBubble.x = initposBubble.x + speed.x * t;
		posBubble.y = initposBubble.y + speed.y * t + 0.5 * g * t * t;
		initposBubble = posBubble;
		speed.y += g * t;
		speed.x *= -1;
		t = 0.1;
	}

	

	sprite->setPosition(glm::vec2(float(posBubble.x), float(posBubble.y)));
}

void Bubble::render()
{
	sprite->render();
}

void Bubble::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bubble::setPosition(const glm::vec2& pos)
{
	posBubble = pos;
	sprite->setPosition(glm::vec2(float(posBubble.x), float(posBubble.y)));
}

glm::ivec2 Bubble::getPosition()
{
	return posBubble;
}

glm::vec2 Bubble::getSpeed()
{
	return glm::vec2(speed.x, speed.y + g*t);
}

bool Bubble::circle_test(const glm::ivec2& pos)
{
	return ((posBubble.x - pos.x) * (posBubble.x - pos.x) + (posBubble.y - pos.y) * (posBubble.y - pos.y)) <= sizeQuad.y * sizeQuad.y;
}

glm::ivec2 Bubble::getSize() {
	return sizeQuad;
}
