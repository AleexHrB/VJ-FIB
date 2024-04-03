#include "BreakableBlock.h"
#include<iostream>

void BreakableBlock::init(const glm::ivec2& inPos, bool horizontal, unsigned int size, unsigned int color, int tileSize)
{
	if (horizontal) {
		spritesheet.loadFromFile("images/horizontal.png", TEXTURE_PIXEL_FORMAT_RGBA);
		this->position = glm::ivec2(inPos.x*tileSize, inPos.y*tileSize);
		this->size = glm::vec2(tileSize*((size - 1) %4 + 1),tileSize);
		this->color = color % 3;
	}
		
	else {
		this->position = inPos;
		this->size = glm::vec2(tileSize, tileSize * ((size - 1) % 4 + 1));
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
	this->tileSize = tileSize;
}


void BreakableBlock::render()
{
	if(!broken) sprite->render();
}

void BreakableBlock::prepareArrays(ShaderProgram& shaderProgram)
{
	if (horizontal) {
		sprite = Sprite::createSprite(size, glm::vec2((size.x / tileSize) / 10.0, 1.0 / 15.0), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);
		sprite->setAnimationSpeed(0, 1);
		//0, 1, 3, 7  --> size - 1 + size - 2
		int temp = size.x / tileSize;

		sprite->addKeyframe(0, glm::vec2( ((temp*(temp - 1))/2)/ 10.0, (color % 3) / 3.0));
		sprite->changeAnimation(0);

		sprite->loopAnimation(1, false);
		sprite->setAnimationSpeed(1, 8);
		sprite->addKeyframe(1, glm::vec2(((temp * (temp - 1)) / 2) / 10.0, (color % 3) / 3.0 + 1 /15.0));
		sprite->addKeyframe(1, glm::vec2(((temp * (temp - 1)) / 2) / 10.0, (color % 3) / 3.0 + 2 / 15.0));
		sprite->addKeyframe(1, glm::vec2(((temp * (temp - 1)) / 2) / 10.0, (color % 3) / 3.0 + 3 / 15.0));
		sprite->addKeyframe(1, glm::vec2(((temp * (temp - 1)) / 2) / 10.0, (color % 3) / 3.0 + 4 / 15.0));
	}
	else {
		sprite = Sprite::createSprite(size, glm::vec2(1.0 / 10.0, (size.x / tileSize) / 15.0), &spritesheet, &shaderProgram);
	}
	sprite->setPosition(position);
}

glm::ivec2 BreakableBlock::getPosition()
{
	return position;
}

int BreakableBlock::getSize()
{
	if (horizontal)
		return size.x / tileSize;
	else
		return size.y / tileSize;
}

glm::ivec2* BreakableBlock::getBlocks()
{
	if (horizontal) {
		int siz = size.x / tileSize;
		glm::ivec2* ret = new glm::ivec2 [siz];
		for (int i = 0; i < siz; ++i) {
			ret[i] = glm::ivec2(position.x / tileSize + i, position.y / tileSize);
		}
		return ret;
	}
	else {

	}
	return nullptr;
}

void BreakableBlock::destroy()
{
	breaking = true;
	sprite->setNextAnimation(0);
	sprite->changeAnimation(1);
}

void BreakableBlock::update(int deltatime)
{
	sprite->update(deltatime);
	if (breaking && sprite->animation() == 0) broken = true;
}

int BreakableBlock::getBouns()
{
	return bonus;
}

