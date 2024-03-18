#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	glm::ivec2 getHookPosition();
	void setShoot(bool hit_hook);
	bool substract_live();
	bool hook_test(const glm::ivec2& posBubble, const glm::ivec2& sizeBubble);
	int get_lives();
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	struct hook {
		Sprite* sprite;
		glm::ivec2 tilePos, posHook;
		Texture spritesheet;
		ShaderProgram sh;
	};
	bool shoot = false;
	hook hk;
	unsigned int lives = 3;
	bool god_mode = false;
	bool G_pressed;

};


#endif // _PLAYER_INCLUDE


