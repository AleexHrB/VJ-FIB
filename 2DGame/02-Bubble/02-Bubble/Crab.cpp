#include "Crab.h"

enum Animation {
	LEFT,
	RIGHT, 
	SIZE
};

void Crab::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Lluc.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizeQuad = glm::ivec2(40,40);
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 3.0, 1.0), &spritesheet, &shaderProgram);
	this->speed = glm::ivec2(8,0);
	this->initPos = this -> position = glm::ivec2(2, 365);
	sprite->setPosition(initPos);

	sprite->setNumberAnimations(SIZE);

	sprite->setAnimationSpeed(LEFT, 2);
	sprite->addKeyframe(LEFT, glm::vec2(1.0 / 3.0, 0.f));

	sprite->setAnimationSpeed(RIGHT, 2);
	sprite->addKeyframe(RIGHT, glm::vec2(2.0 / 3.0, 0.f));

	sprite->changeAnimation(LEFT);
}

void Crab::update(int deltaTime)
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
		left_anim = !left_anim;
		t_anim = 0;
	}

	if (left_anim) sprite->changeAnimation(LEFT);
	else sprite->changeAnimation(RIGHT);
}

unsigned int Crab::getBonus()
{
	return 100;
}
