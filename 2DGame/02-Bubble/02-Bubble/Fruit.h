#pragma once
#ifndef _FRUIT_INCLUDE
#define _FRUIT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Fruit
{


public:

	enum FruitType {
		CHERRY,
		LEMON,
		BANNANA,
		ORANGE,
		WATERMELON,
		PINEAPPLE,
		GRAPES,
		APPLE,
		STRAWBERRY,
		MELON
	};

	void init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size, FruitType type);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	glm::vec2 getSpeed();
	//bool circle_test(const glm::ivec2& pos);
	glm::ivec2 getSize();
	pair<glm::ivec2, glm::ivec2> getHitboxFruit();
	unsigned int getBonus();

private:
	glm::ivec2 posFruit, sizeQuad;
	inline void calculateBonus();
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	//Needed for projectile motion equations
	glm::vec2 speed;
	float t = 0;
	float g = 1.8;
	bool b = true;
	float t_anim = 0;
	unsigned int points;

};


#endif // _PLAYER_INCLUDE