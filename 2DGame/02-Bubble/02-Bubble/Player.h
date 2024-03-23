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


class Player : public Entity
{

public:

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	void update(int deltaTime) override; 
	void render() override;
	void hitWeapon();
	bool substractLive();
	int getLives();
	void changeWeapon(Effects t);
	pair<glm::ivec2, glm::ivec2> getWeaponHitbox();
	bool checkProjectileHitbox(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b);
private:
	bool bJumping = false;
	int jumpAngle, startY;
	bool shoot = false;
	unsigned int lives = 3;
	bool god_mode = false;
	bool G_pressed;
	bool C_pressed;
	Effects actual_weapon;
	Weapon* w = nullptr;

};


#endif // _PLAYER_INCLUDE


