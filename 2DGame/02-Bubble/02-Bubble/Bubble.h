#ifndef _BUBBLE_INCLUDE
#define _BUBBLE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Bubble
{

public:
	void init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, const glm::ivec2& size, unsigned int color);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	glm::vec2 getSpeed();
	bool circle_test(const glm::ivec2& pos);
	glm::ivec2 getSize();
	enum {
		RED,
		BLUE,
		GREEN
	};

private:
	glm::ivec2 posBubble, sizeQuad;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	//Needed for projectile motion equations
	glm::vec2 speed, initposBubble, actualSpeed;
	float t = 0;
	float g = 1.8;

};


#endif // _PLAYER_INCLUDE