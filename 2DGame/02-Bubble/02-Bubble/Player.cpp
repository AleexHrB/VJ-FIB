#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	float unit = 0.14285714285;
	bJumping = false;
	sizeQuad = glm::ivec2(64, 64);
	this->texProgram = shaderProgram;
	spritesheet.loadFromFile("images/Pedro.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(sizeQuad, glm::vec2(unit, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(PlayerAnims::SIZE);
	
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

		sprite->loopAnimation(SHOOT, false);
		sprite->setAnimationSpeed(SHOOT, 16);
		sprite->addKeyframe(SHOOT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(SHOOT, glm::vec2(0.f, 0.5f));

		sprite->setAnimationSpeed(CLIMB, 16);
		sprite->addKeyframe(CLIMB, glm::vec2(unit*4,0.5f));
		sprite->addKeyframe(CLIMB, glm::vec2(unit * 4, 0.f));
		sprite->addKeyframe(CLIMB, glm::vec2(unit * 4, 0.5f));
		sprite->addKeyframe(CLIMB, glm::vec2(unit * 5, 0.f));
		
	sprite->changeAnimation(0);
	lastAnim = STAND_LEFT;
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

	if (Game::instance().getKey(GLFW_KEY_C) && !C_pressed)
	{
		if (w->shoot(position + sizeQuad / 2)) {
			sprite->setNextAnimation(sprite->animation());
			sprite->changeAnimation(SHOOT);
		}
		
				
		C_pressed = true;		
	}
	

	else if(Game::instance().getKey(GLFW_KEY_LEFT) && sprite->animation() != SHOOT)
	{
		if (sprite->animation() != MOVE_LEFT) {
			sprite->changeAnimation(MOVE_LEFT);
		}

		position.x -= speed.x;
		if(map->collisionMoveLeft(position, glm::ivec2(32, 32)))
		{
			position.x += speed.x;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getKey(GLFW_KEY_RIGHT) && sprite->animation() != SHOOT)
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

	else if (Game::instance().getKey(GLFW_KEY_UP) && sprite->animation() != SHOOT)
	{
		if (map->getTileType(position + glm::ivec2(sizeQuad.x / 2, 0)) != TileMap::TileType::SolidBlock) {
			if (map->getTileType(position + glm::ivec2(sizeQuad.x / 2, 0)) == TileMap::TileType::Ladder) {
				position.y -= 6;
				if (sprite->animation() != CLIMB) 
					sprite->changeAnimation(CLIMB);
			}
			else if (map->getTileType(position + glm::ivec2(sizeQuad.x / 2, sizeQuad.y)) == TileMap::TileType::Ladder) {
				position.y -= 6;
				if (sprite->animation() != CLIMB)
					sprite->changeAnimation(CLIMB);
			}
		}
	}
	
	else if (Game::instance().getKey(GLFW_KEY_DOWN) && sprite->animation() != SHOOT)
	{	
		if (map->getTileType(position + glm::ivec2(sizeQuad.x / 2, sizeQuad.y)) != TileMap::TileType::SolidBlock) {
			if (map->getTileType(position + glm::ivec2(sizeQuad.x / 2, 0)) == TileMap::TileType::Ladder) position.y += 2;
			else if (map->getTileType(position + glm::ivec2(sizeQuad.x / 2, sizeQuad.y)) == TileMap::TileType::Ladder) position.y += 2;
		}
	}
	

	else
	{

		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);

	}

	if (!Game::instance().getKey(GLFW_KEY_C)) {
		C_pressed = false;
	}

	if (bJumping)
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
		if (!map->getTileType(position + glm::ivec2(0, sizeQuad.y)) == TileMap::TileType::Ladder && !map->getTileType(position + sizeQuad) == TileMap::TileType::Ladder) position.y += FALL_STEP;
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

	lastAnim = PlayerAnims(sprite->animation());
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
	--lives;

	return lives == 0;
}

int Player::getLives() {
	return lives;
}

void Player::changeWeapon(Effects eff)
{
	this->actual_weapon = eff;

	switch (eff) {
	case Effects::GUN:
		delete w;
		w = new Gun();
		w->init(glm::ivec2(0,0), texProgram);
		break;
	case Effects::STICK:
		delete w;
		w = new StickyHook();
		w->init(glm::ivec2(0, 0), texProgram);
		break;
	case Effects::DOUBLE:
		delete w;
		w = new DoubleHook();
		w->init(glm::ivec2(0, 0), texProgram);
		break;
	case Effects::HOOK:
		delete w;
		w = new Hook();
		w->init(glm::ivec2(0, 0), texProgram);
		break;

	}

	w->setTileMap(map);
}

pair<glm::ivec2, glm::ivec2> Player::getWeaponHitbox()
{
	return w->getHitbox();
}

pair<glm::ivec2, glm::ivec2> Player::getHitbox()
{
	glm::ivec2 hitbox;
	glm::ivec2 offset;
	switch (lastAnim) {
	case PlayerAnims::STAND_LEFT:
		hitbox = glm::ivec2(13,28);
		offset = glm::ivec2(7,3);
		break;
	case PlayerAnims::MOVE_RIGHT:
		hitbox = glm::ivec2(14,30);
		offset = glm::ivec2(6,1);
		break;
	case PlayerAnims::STAND_RIGHT:
		hitbox = glm::ivec2(16,29);
		offset = glm::ivec2(10,2);
		break;
	case PlayerAnims::MOVE_LEFT:
		hitbox = glm::ivec2(16,30);
		offset = glm::ivec2(10,1);
		break;
	case PlayerAnims::SHOOT:
		hitbox = glm::ivec2(16, 27);
		offset = glm::ivec2(6, 4);
		break;
	default:
		hitbox = sizeQuad;
		offset = glm::ivec2(0, 0);
		break;
	}

	return {hitbox * 2, position + offset };
}

bool Player::checkProjectileHitbox(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b)
{
	return w->checkCollisionProj(hitbox, b);
}

void Player::setTileMap(TileMap* tileMap)
{
	this->map = tileMap;
	w->setTileMap(map);
}




