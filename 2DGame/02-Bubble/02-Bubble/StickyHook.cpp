#include "StickyHook.h"
#include <iostream>

void StickyHook::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->texProgram = shaderProgram;
	sprite = Sprite::createSprite(glm::ivec2(9, 6), glm::vec2(1.0f, 0.333f), &spritesheet, &shaderProgram);
}

void StickyHook::update(int deltaTime)
{
	if (stick) {
		t += deltaTime / 100.0;
		if (t > 50) shooted = false;
	}
	if (shooted) {
		if (!map->collisionMoveUp(position, glm::ivec2(9, y0 - position.y), &position.y)) position.y -= 4;
		else {
			bool destroy = map->weaponColision(position, glm::ivec2(9, y0 - position.y));
			if (destroy) shooted = false;
			else if (!stick) {
				stick = true;
				spritesheet.loadFromFile("images/StickHook.png", TEXTURE_PIXEL_FORMAT_RGBA);
			}
		}
		sprite = Sprite::createSprite(glm::ivec2(9, y0 - position.y), glm::vec2(1.0f, (y0 - position.y) / 188.0), &spritesheet, &texProgram);
		sprite->setPosition(glm::vec2(float(position.x), float(position.y)));
	}
}

bool StickyHook::shoot(const glm::ivec2& pos)
{
	if (!shooted) {
		position = pos;
		t = 0;
		stick = false;
		y0 = pos.y + 32;
		shooted = true;
		spritesheet.loadFromFile("images/hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(9, y0 - position.y), glm::vec2(1.0f, (y0 - position.y) / 188.0), &spritesheet, &texProgram);
		return true;
	}
	return false;
}

pair<glm::ivec2, glm::ivec2> StickyHook::getHitbox()
{
	pair<glm::ivec2, glm::ivec2> p = { glm::ivec2(9, y0 - position.y), glm::ivec2(position.x, position.y) };
	pair<glm::ivec2, glm::ivec2> p2 = { glm::ivec2(-1,-1), glm::ivec2(-1,-1) };
	return shooted ? p : p2;
}
