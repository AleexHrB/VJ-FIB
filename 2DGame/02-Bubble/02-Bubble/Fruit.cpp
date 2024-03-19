#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Fruit.h"
#include "Game.h"

enum {
	LEFT,
	RIGHT,
	SIZE
};

void Fruit::init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size, FruitType type)
{

	spritesheet.loadFromFile("images/Fruit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = size;
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 5.0, 1.0 / 2.0), &spritesheet, &shaderProgram);
	this->speed = speed;
	this->posFruit = initPos;
	sprite->setPosition(glm::vec2(float(posFruit.x), float(posFruit.y)));

	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2((type%5) / 5.0, int(type/5)/2));
	sprite->changeAnimation(0);
	calculateBonus();
}

void Fruit::update(int deltaTime)
{
	sprite->update(deltaTime);
	t += deltaTime / 100.0;
	t_anim += deltaTime / 100.0;
	//posFruit = t * speed;
	glm::vec2 pos;
	pos.x = posFruit.x + t * speed.x;
	pos.y = posFruit.y + t * speed.y;
	sprite->setPosition(pos);
	if (t_anim > 5) {
		b = !b;
		t_anim = 0;
	}

	if (b) sprite->changeAnimation(LEFT);
	else sprite->changeAnimation(RIGHT);
}

void Fruit::render()
{
	sprite->render();
}

void Fruit::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Fruit::setPosition(const glm::vec2& pos)
{
	//posFruit = pos;
	sprite->setPosition(pos);
}

glm::ivec2 Fruit::getPosition()
{
	glm::ivec2 pos;
	pos.x = posFruit.x + t * speed.x;
	pos.y = posFruit.y + t * speed.y;
	return pos;
}

glm::vec2 Fruit::getSpeed()
{
	return speed;
}

glm::ivec2 Fruit::getSize() {
	return sizeQuad;
}

pair<glm::ivec2, glm::ivec2> Fruit::getHitboxFruit()
{
	return { sizeQuad, getPosition() };
}

unsigned int Fruit::getBonus()
{
	return points;
}

inline void Fruit::calculateBonus()
{
	//Esto estaría bien poner un switch con todos los tipos de frutas y con ello calcular los puntos que te da
	points = 1000;
}
