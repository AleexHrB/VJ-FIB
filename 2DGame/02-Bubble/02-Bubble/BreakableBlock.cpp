#include "BreakableBlock.h"
#include<iostream>

void BreakableBlock::init(const glm::ivec2& inPos, bool horizontal, unsigned int size, unsigned int color)
{
	if (horizontal) {
		spritesheet.loadFromFile("images/horizontal.png", TEXTURE_PIXEL_FORMAT_RGBA);
		this->position = glm::ivec2(inPos.x*16, inPos.y*16);
		this->size = glm::vec2(16*((size - 1) %4 + 1),16);
		this->color = color % 3;
	}
		
	else {
		this->position = inPos;
		this->size = glm::vec2(16, 16 * ((size - 1) % 4 + 1));
		this->color = color % 3;
		spritesheet.loadFromFile("images/vertical.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}	
		
	
	this->horizontal = horizontal;


	/*sprite->setNumberAnimations(SIZE);

	sprite->setAnimationSpeed(LEFT, 2);
	sprite->addKeyframe(LEFT, glm::vec2(1.0 / 3.0, 0.f));

	sprite->setAnimationSpeed(RIGHT, 2);
	sprite->addKeyframe(RIGHT, glm::vec2(2.0 / 3.0, 0.f));

	sprite->changeAnimation(LEFT);*/
}


void BreakableBlock::render()
{
	sprite->render();
}

void BreakableBlock::prepareArrays(ShaderProgram& shaderProgram)
{
	if (horizontal) {
		sprite = Sprite::createSprite(size, glm::vec2((size.x / 16) / 10.0, 1.0 / 15.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);
		sprite->setAnimationSpeed(0, 1);
		//0, 1, 3, 7  --> size - 1 + size - 2
		int temp = size.x / 16;

		sprite->addKeyframe(0, glm::vec2( ((temp*(temp - 1))/2)/ 10.0, (color % 3) / 3.0));
		sprite->changeAnimation(0);
	}
	else {
		sprite = Sprite::createSprite(size, glm::vec2(1.0 / 10.0, (size.x / 16) / 15.0), &spritesheet, &shaderProgram);
	}
	sprite->setPosition(position);
}

glm::ivec2 BreakableBlock::getPosition()
{
	return glm::ivec2();
}
