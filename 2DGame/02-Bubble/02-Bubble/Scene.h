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

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	void treatPowerUp(Effects f);
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
	bool godMode = true;
	unsigned int timeLimit;

	list<Bubble*> lB;
	list<Enemy*> lE;
	list<Object*> lO;
};


#endif // _SCENE_INCLUDE

