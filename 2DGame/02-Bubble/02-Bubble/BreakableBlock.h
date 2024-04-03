#pragma once
#include <glm/detail/type_vec.hpp>
#include "Sprite.h"

class BreakableBlock
{
public:
	void init(const glm::ivec2& inPos, bool horizontal, unsigned int size, unsigned int color, int tileSize);
	void render();
	void prepareArrays(ShaderProgram &shaderProgram);
	glm::ivec2 getPosition();
	int getSize();
	glm::ivec2* getBlocks();
	void destroy();
	void update(int deltatime);
	int getBouns();

protected:
	glm::ivec2 position, size;
	Texture spritesheet;
	int color;
	bool horizontal;
	bool breaking = false;
	bool broken = false;
	ShaderProgram texProgram;
	Sprite* sprite;
	float g = 1.8;
	int bonus = 200;
	int tileSize;
};

