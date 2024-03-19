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
#include "Fruit.h"
#include "PowerUp.h"


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
	float currentTime;
	float inmuneTime = 0.0f;
	glm::mat4 projection;
	list<Bubble*> l;
	list<Fruit*> l_f;
	list<Enemy*> l_e;
	list<PowerUp*> l_p;
	inline bool hitted();
	//inline bool hook_test(const glm::ivec2& bub);
	Text text;
	bool menu;
	int score;
	unsigned int level;
	unsigned int timeLimit;
	inline bool hitRectangle(const pair<glm::ivec2, glm::ivec2>& r1, const pair<glm::ivec2, glm::ivec2>& r2);
	inline bool hitCircle(const pair<glm::ivec2, glm::ivec2>& c, const pair<glm::ivec2, glm::ivec2>& r1);
	inline int getMinimumDistance (int minEdge, int maxEdge, int centerCoord) {
		if (centerCoord >= minEdge && centerCoord <= maxEdge) {
			// The center is inside the rectangle along this axis, so distance is 0.
			return 0;
		}
		// The center is outside the rectangle; calculate the distance to the closer edge.
		return centerCoord < minEdge ? minEdge - centerCoord : centerCoord - maxEdge;
	}
};


#endif // _SCENE_INCLUDE

