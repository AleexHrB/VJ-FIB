#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <list>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Bubble.h"
#include "text.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(const string &level, bool menu);
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	float inmuneTime = 0.0f;
	glm::mat4 projection;
	list<Bubble*> l;
	inline bool hitted();
	inline bool hook_test(const glm::ivec2& bub);
	Text text;
	bool menu;
};


#endif // _SCENE_INCLUDE

