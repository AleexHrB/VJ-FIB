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
	spritesheet.loadFromFile("images/Pedro.png", TEXTURE_PIXEL_FORMAT_RGBA);
	hk.sh = shaderProgram;
	hk.spritesheet.loadFromFile("images/hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(unit, 0.5), &spritesheet, &shaderProgram);
	hk.sprite = Sprite::createSprite(glm::ivec2(9, 6), glm::vec2(1.0f,0.333f), &hk.spritesheet, &shaderProgram);
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
	//hk.sprite->setNumberAnimations(1);

	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey(GLFW_KEY_C))
	{
		hk.posHook = posPlayer;
		hk.posHook += 32;
		shoot = true;
		if (sprite->animation() != SHOOT)
			sprite->changeAnimation(SHOOT);
	}
	else if(Game::instance().getKey(GLFW_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getKey(GLFW_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	

	else if (Game::instance().getKey(GLFW_KEY_G))
	{
		if (!G_pressed) {
			god_mode = !god_mode;
			G_pressed = true;
		}
		cout << "God mode = " << god_mode << endl;
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
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y))
		{
			/*if (Game::instance().getKey(GLFW_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}*/
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	if (shoot) {
		hk.sprite = Sprite::createSprite(glm::ivec2(9, ((posPlayer.y + 64) - hk.posHook.y)), glm::vec2(1.0f, (posPlayer.y - hk.posHook.y) / 188.0), &hk.spritesheet, &hk.sh);
		if (hk.posHook.y > 16) hk.posHook.y -= 4;
		else shoot = false;
		hk.sprite->setPosition(glm::vec2(float(tileMapDispl.x + hk.posHook.x), float(tileMapDispl.y + hk.posHook.y)));
	}
}

void Player::render()
{
	sprite->render();
	if (shoot) hk.sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

glm::ivec2 Player::getHookPosition()
{
	return hk.posHook;
}

void Player::setShoot(bool hit_hook)
{
	this->shoot = hit_hook;
}

bool Player::substract_live()
{
	if (!god_mode) --lives;

	return lives == 0;
}

//9x6
bool Player::hook_test(const glm::ivec2& posBubble)
{
	//Left
	glm::ivec2 pos_l = posBubble + glm::ivec2(0,40);
	glm::ivec2 pos_r = posBubble + glm::ivec2(48, 40);
	bool b1 = pos_l.x <= hk.posHook.x && hk.posHook.y <= pos_l.y;
	bool b2 = pos_r.x >= (hk.posHook.x + 9);
	return b1 && b2 && shoot;
}


