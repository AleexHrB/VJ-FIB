#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"
#include "Weapon.h"
#include "Gun.h"
#include "Hook.h"
#include "StickyHook.h"
#include "DoubleHook.h"
#include "Effects.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.
#define DISABLED_TIME 3000

class Player : public Entity
{

public:

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	void update(int deltaTime) override; 
	void render(bool flicker, glm::vec4 color);
	void hitWeapon();
	bool substractLive();
	int getLives();
	void changeWeapon(Effects t);
	pair<glm::ivec2, glm::ivec2> getWeaponHitbox();
	pair<glm::ivec2, glm::ivec2> getHitbox() override;
	bool checkProjectileHitbox(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b);
	void setTileMap(TileMap* tileMap) override;
	void setLives(int liv);
	void setDisabled(bool disable);
	bool isDisabled();
private:
	bool bJumping = false;
	int jumpAngle, startY;
	int disabledTime = 0;
	bool shoot = false;
	bool disabled = false;
	unsigned int lives = 3;
	bool C_pressed,UP_pressed, DOWN_pressed;
	Effects actual_weapon;
	Weapon* w = nullptr;


	enum PlayerAnims
	{
		STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, SHOOT, CLIMB, IDLE_CLIMB, DIE_RIGHT, DIE_LEFT, SIZE
	};

	PlayerAnims lastAnim;

};


#endif // _PLAYER_INCLUDE


