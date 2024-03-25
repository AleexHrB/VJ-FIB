#pragma once
#include <glm/detail/type_vec.hpp>
#include "Sprite.h"

class BreakableBlock
{
public:
	void init(const glm::ivec2& inPos, bool horizontal, unsigned int size, unsigned int color);
	void render();
	void prepareArrays(ShaderProgram &shaderProgram);
	glm::ivec2 getPosition();

protected:
	glm::ivec2 position, size;
	Texture spritesheet;
	int color;
	bool horizontal;
	ShaderProgram texProgram;
	Sprite* sprite;
	float g = 1.8;
};

