#include "Fruit.h"

void Fruit::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
}

void Fruit::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Effects f, const glm::vec2& pos)
{
	spritesheet.loadFromFile("images/Fruit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = pos;
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(f / 6 * 0.5, f%6 / 5.0), &spritesheet, &shaderProgram);
	this->speed = glm::ivec2(g, 0);
	this->position = pos;
	sprite->setPosition(pos);
	this->f = f;
}

unsigned int Fruit::getBonus()
{
    return 1000;
}

Effects Fruit::applyEffect()
{
    return f;
}
