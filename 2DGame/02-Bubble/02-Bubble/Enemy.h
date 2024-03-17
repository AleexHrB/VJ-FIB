#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy
{

public:
	void init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	glm::vec2 getSpeed();
	//bool circle_test(const glm::ivec2& pos);
	glm::ivec2 getSize();

private:
	glm::ivec2 posEnemy, sizeQuad;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	//Needed for projectile motion equations
	glm::vec2 speed;
	float t = 0;
	float g = 1.8;
	bool b = true;
	float t_anim = 0;

};


#endif // _PLAYER_INCLUDE