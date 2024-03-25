#include "Bird.h"
#include <iostream>

enum Anim {
	UP_L,
	DOWN_L,
	UP_R,
	DOWN_R,
	SIZE
};
void Bird::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Sebastian.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = glm::ivec2(40, 40);
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 5.0, 1.0), &spritesheet, &shaderProgram);
	this->speed = glm::ivec2(14, 0);
	this->initPos = this->position = glm::ivec2(0, 170);
	sprite->setPosition(initPos);

	sprite->setNumberAnimations(SIZE);

	sprite->setAnimationSpeed(DOWN_L, 2);
	sprite->addKeyframe(DOWN_L, glm::vec2(1.0 / 5.0, 0.f));

	sprite->setAnimationSpeed(UP_L, 2);
	sprite->addKeyframe(UP_L, glm::vec2(0.0, 0.0));

	sprite->setAnimationSpeed(UP_R, 2);
	sprite->addKeyframe(UP_R, glm::vec2(4.0/5.0, 0.0));


	sprite->setAnimationSpeed(DOWN_R, 2);
	sprite->addKeyframe(DOWN_R, glm::vec2(3.0/5.0, 0.0));

	sprite->changeAnimation(UP_L);

}

void Bird::update(int deltaTime)
{
	sprite->update(deltaTime);
	t += deltaTime / 100.0;
	t_anim += deltaTime / 100.0;
	if (position.x > 800 || position.x < -100) {
		this->speed.x *= -1;
		t = 1;
		initPos = position;
	}

	position.x = initPos.x + t * speed.x;
	position.y = initPos.y + t * speed.y;
	sprite->setPosition(position);

	if (t_anim > 5) {
		up_anim = !up_anim;
		t_anim = 0;
	}

	if (up_anim) sprite->changeAnimation(speed.x < 0 ? UP_R : UP_L);
	else sprite->changeAnimation(speed.x < 0 ? DOWN_R : DOWN_L);
}

unsigned int Bird::getBonus()
{
	return 500;
}
