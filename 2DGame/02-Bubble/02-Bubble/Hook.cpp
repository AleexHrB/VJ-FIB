#include "Hook.h"
#include <iostream>

void Hook::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->texProgram = shaderProgram;
	sprite = Sprite::createSprite(glm::ivec2(9, 6), glm::vec2(1.0f, 0.333f), &spritesheet, &shaderProgram);
}

void Hook::update(int deltaTime)
{
	if (shooted) {
		if (position.y > 16) position.y -= 4;
		else shooted = false;
		sprite = Sprite::createSprite(glm::ivec2(9, 400 - position.y), glm::vec2(1.0f, (400 - position.y) / 188.0), &spritesheet, &texProgram);
		sprite->setPosition(glm::vec2(float(position.x), float(position.y)));
	}
}

void Hook::shoot(const glm::ivec2& pos)
{
	if (!shooted) {
		
		position = pos;
		shooted = true;
	}
}
