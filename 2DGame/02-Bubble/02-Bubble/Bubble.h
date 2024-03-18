#ifndef _BUBBLE_INCLUDE
#define _BUBBLE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Bubble
{

public:
	enum Color {
		RED,
		BLUE,
		GREEN
	};

	enum Size {
		BIG,
		MIDDLE,
		SMALL,
		TINY,
		NONE
	};
	void init(ShaderProgram& shaderProgram, const glm::ivec2& initPos, const glm::ivec2& speed, Color color, Size s);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	glm::vec2 getSpeed();
	bool circle_test(const glm::ivec2& pos);
	Size getSize();
	Size getNextSize();
	glm::ivec2 getSizeV();
	pair<glm::ivec2, glm::ivec2> getHitboxBubble();
private:
	glm::ivec2 posBubble, sizeQuad;
	Size sizeQuadEnum;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	//Needed for projectile motion equations
	glm::vec2 speed, initposBubble, actualSpeed;
	float t = 0;
	float g = 1.8;

};


#endif // _PLAYER_INCLUDE