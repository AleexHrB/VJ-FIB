#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Bubble.h"
#include "Game.h"


void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	
	spritesheet.loadFromFile("images/Bubbles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 40), glm::vec2(1, 1.0/3.0), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	speed.x = 4;
	speed.y = 4;
	posPlayer.x = 10;
	posPlayer.y = 20;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Bubble::update(int deltaTime)
{
	sprite->update(deltaTime);
	posPlayer.x += speed.x;
	posPlayer.y += speed.y;
	
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
		posPlayer.y = posPlayer.y - speed.y;
		posPlayer.x = posPlayer.x - speed.x;
		speed.y = speed.y * -1;
	}

	if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)) || map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
	{
		posPlayer.y = posPlayer.y - speed.y;
		posPlayer.x = posPlayer.x - speed.x;
		speed.x = speed.x * -1;
	}

	

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}