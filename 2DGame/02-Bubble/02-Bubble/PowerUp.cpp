#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "PowerUp.h"
#include "Game.h"

enum {
	LEFT,
	RIGHT,
	SIZE
};

void PowerUp::init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size, PowerUpType type)
{

	spritesheet.loadFromFile("images/powerup.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = size;
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 3.0, 1.0), &spritesheet, &shaderProgram);
	this->speed = speed;
	this->posPowerUp = initPos;
	sprite->setPosition(glm::vec2(float(posPowerUp.x), float(posPowerUp.y)));

	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2((type % 3) / 3.0, 0));
	sprite->changeAnimation(0);
}

void PowerUp::update(int deltaTime)
{
	sprite->update(deltaTime);
	t += deltaTime / 100.0;
	t_anim += deltaTime / 100.0;
	//posPowerUp = t * speed;
	glm::vec2 pos;
	pos.x = posPowerUp.x + t * speed.x;
	pos.y = posPowerUp.y + t * speed.y;
	sprite->setPosition(pos);
	if (t_anim > 5) {
		b = !b;
		t_anim = 0;
	}

	if (b) sprite->changeAnimation(LEFT);
	else sprite->changeAnimation(RIGHT);
}

void PowerUp::render()
{
	sprite->render();
}

void PowerUp::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PowerUp::setPosition(const glm::vec2& pos)
{
	//posPowerUp = pos;
	sprite->setPosition(pos);
}

glm::ivec2 PowerUp::getPosition()
{
	glm::ivec2 pos;
	pos.x = posPowerUp.x + t * speed.x;
	pos.y = posPowerUp.y + t * speed.y;
	return pos;
}

glm::vec2 PowerUp::getSpeed()
{
	return speed;
}

glm::ivec2 PowerUp::getSize() {
	return sizeQuad;
}

pair<glm::ivec2, glm::ivec2> PowerUp::getHitboxPowerUp()
{
	return { sizeQuad, getPosition() };
}