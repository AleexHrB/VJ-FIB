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
	speed.x = 10;
	speed.y = 0;
	posPlayer.x = initPosPlayer.x = 10;
	posPlayer.y = initPosPlayer.y = 200;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Bubble::update(int deltaTime)
{
	sprite->update(deltaTime);
	t += deltaTime / 100.0;
	posPlayer.x = initPosPlayer.x + speed.x * t;
	posPlayer.y = initPosPlayer.y + speed.y * t + 0.5 * g * t * t;

	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
		t -= 2*deltaTime / 100.0;
		posPlayer.x = initPosPlayer.x + speed.x * t;
		posPlayer.y = initPosPlayer.y + speed.y * t + 0.5 * g * t * t;
		initPosPlayer = posPlayer;
		speed.y += g*t;
		speed.y *= -1;
		t = 0.1;
	}
	
	if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)) || map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
	{
		t -= 2*deltaTime / 100.0;
		posPlayer.x = initPosPlayer.x + speed.x * t;
		posPlayer.y = initPosPlayer.y + speed.y * t + 0.5 * g * t * t;
		initPosPlayer = posPlayer;
		speed.y += g * t;
		speed.x *= -1;
		t = 0.1;
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