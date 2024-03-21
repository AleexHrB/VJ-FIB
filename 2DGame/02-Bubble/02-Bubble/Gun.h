#pragma once
#include "Weapon.h"
class Gun : public Weapon
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void shoot(const glm::ivec2& pos) override;
};

