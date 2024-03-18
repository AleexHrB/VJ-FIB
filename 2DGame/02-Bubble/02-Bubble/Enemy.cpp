#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Enemy.h"
#include "Game.h"

enum {
	LEFT,
	RIGHT,
	SIZE
};

void Enemy::init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size)
{

	spritesheet.loadFromFile("images/Lluc.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = size;
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0/3.0, 1.0), &spritesheet, &shaderProgram);
	this->speed = speed;
	this->posEnemy = initPos;
	sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));

	sprite->setNumberAnimations(SIZE);

	sprite->setAnimationSpeed(LEFT, 2);
	sprite->addKeyframe(LEFT, glm::vec2(1.0/3.0, 0.f));

	sprite->setAnimationSpeed(RIGHT, 2);
	sprite->addKeyframe(RIGHT, glm::vec2(2.0/3.0, 0.f));

	sprite->changeAnimation(LEFT);
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	t += deltaTime / 100.0;
	t_anim += deltaTime / 100.0;
	//posEnemy = t * speed;
	glm::vec2 pos;
	pos.x = posEnemy.x + t * speed.x;
	pos.y = posEnemy.y + t * speed.y;
	sprite->setPosition(pos);
	if (t_anim > 5) {
		b = !b;
		t_anim = 0;
	}

	if (b) sprite->changeAnimation(LEFT);
	else sprite->changeAnimation(RIGHT);
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	//posEnemy = pos;
	sprite->setPosition(pos);
}

glm::ivec2 Enemy::getPosition()
{
	glm::ivec2 pos;
	pos.x = posEnemy.x + t * speed.x;
	pos.y = posEnemy.y + t * speed.y;
	return pos;
}

glm::vec2 Enemy::getSpeed()
{
	return speed;
}

glm::ivec2 Enemy::getSize() {
	return sizeQuad;
}

pair<glm::ivec2, glm::ivec2> Enemy::getHitboxEnemy()
{
	return {sizeQuad, getPosition()};
}
