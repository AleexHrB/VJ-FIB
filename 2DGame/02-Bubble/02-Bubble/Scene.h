#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <list>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Bubble.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
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
	inline bool circle_test(glm::ivec2 posBubble);
	inline bool hitted();
	inline bool hook_test(glm::ivec2& posBubble);

};


#endif // _SCENE_INCLUDE

