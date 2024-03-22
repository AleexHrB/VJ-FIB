#pragma once
#include "Enemy.h"

class Bird : public Enemy
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	unsigned int getBonus() override;
private:
	float t = 0;
	float t_anim = 0;
	bool up_anim = false;
	glm::ivec2 initPos;
};

