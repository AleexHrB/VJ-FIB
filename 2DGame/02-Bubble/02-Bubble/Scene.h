#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <list>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Bubble.h"
#include "Enemy.h"
#include "text.h"
#include "Crab.h"
#include "Bird.h"
#include "Object.h"
#include "SoundManager.h"

#define DEATH_FRAMES 15
#define READY_FRAMES 15

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(unsigned int level);
	void update(int deltaTime);
	void render();
	void treatPowerUp(Effects f);
	void changeGodMode();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	void explodeBubbles();
	float currentTime;
	float inmuneTime = 0.0f;
	glm::mat4 projection;
	inline bool hitted();
	Text text;
	bool menu;
	bool freeze = false;
	int score;
	unsigned int level;
	bool godMode = false;
	unsigned int timeLimit;
	unsigned int mult = 1;
	Bubble::Size lastSize = Bubble::Size::NONE;
	void updatePowerUps(int deltaTime);
	Texture UI;
	Sprite* liveSprite;
	Sprite* powerUp;
	int deathCountDown = -1;

	list<Bubble*> lB;
	list<Enemy*> lE;
	list<Object*> lO;

	float powerUpTimers[Effects::SIZE_EFF];
};


#endif // _SCENE_INCLUDE

