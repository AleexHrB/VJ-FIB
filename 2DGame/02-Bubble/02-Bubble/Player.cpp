#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, SHOOT, SIZE
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	float unit = 0.14285714285;
	bJumping = false;
	sizeQuad = glm::ivec2(64, 64);
	spritesheet.loadFromFile("images/Pedro.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(unit, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(SIZE);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(2*unit, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 6);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(3*unit, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(3*unit, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 6);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(unit, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(unit, 0.5f));

		sprite->setAnimationSpeed(SHOOT, 16);
		sprite->addKeyframe(SHOOT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(SHOOT, glm::vec2(0.f, 0.5f));
		
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
	speed = glm::ivec2(3, 3);
	w = new Hook();
	w->init(tileMapPos, shaderProgram);
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	w->update(deltaTime);
	if (Game::instance().getKey(GLFW_KEY_C))
	{
			w->shoot(position + sizeQuad/2);
			if (sprite->animation() != SHOOT)
				sprite->changeAnimation(SHOOT);
	}
	else if(Game::instance().getKey(GLFW_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		position.x -= speed.x;
		if(map->collisionMoveLeft(position, glm::ivec2(32, 32)))
		{
			position.x += speed.x;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getKey(GLFW_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		position.x += speed.x;
		if(map->collisionMoveRight(position, glm::ivec2(32, 32)))
		{
			position.x -= speed.x;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	

	else if (Game::instance().getKey(GLFW_KEY_G))
	{
		if (!G_pressed) {
			god_mode = !god_mode;
			G_pressed = true;
		}
	}
	else
	{
		
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		G_pressed = false;
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			position.y = startY;
		}
		else
		{
			position.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(position, glm::ivec2(64, 64), &position.y);
		}
	}
	else
	{
		position.y += FALL_STEP;
		if(map->collisionMoveDown(position, glm::ivec2(64, 64), &position.y))
		{
			/*if (Game::instance().getKey(GLFW_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}*/
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void Player::render()
{
	sprite->render();
	w->render();
}


void Player::hitWeapon()
{
	w ->hitted();
}

bool Player::substractLive()
{
	if (!god_mode) --lives;

	return lives == 0;
}

int Player::getLives() {
	return lives;
}

void Player::changeWeapon(Types t)
{
	this->actual_weapon = t;
}

pair<glm::ivec2, glm::ivec2> Player::getWeaponHitbox()
{
	return w->getHitbox();
}




