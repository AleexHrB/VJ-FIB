#include "StickyHook.h"

void StickyHook::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->texProgram = shaderProgram;
	sprite = Sprite::createSprite(glm::ivec2(9, 6), glm::vec2(1.0f, 0.333f), &spritesheet, &shaderProgram);
}

void StickyHook::update(int deltaTime)
{
	if (shooted) {
		if (position.y > 16) position.y -= 4;
		else spritesheet.loadFromFile("images/StickHook.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(9, y0 - position.y), glm::vec2(1.0f, (y0 - position.y) / 188.0), &spritesheet, &texProgram);
		sprite->setPosition(glm::vec2(float(position.x), float(position.y)));
	}
}

void StickyHook::shoot(const glm::ivec2& pos)
{
	if (!shooted) {
		spritesheet.loadFromFile("images/Hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
		position = pos;
		y0 = pos.y + 32;
		shooted = true;
	}
}

pair<glm::ivec2, glm::ivec2> StickyHook::getHitbox()
{
	pair<glm::ivec2, glm::ivec2> p = { glm::ivec2(9, y0 - position.y), glm::ivec2(position.x, position.y) };
	pair<glm::ivec2, glm::ivec2> p2 = { glm::ivec2(-1,-1), glm::ivec2(-1,-1) };
	return shooted ? p : p2;
}
