#pragma once
#include "Weapon.h"
class StickyHook : public Weapon
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void shoot(const glm::ivec2& pos) override;
	pair<glm::ivec2, glm::ivec2> getHitbox() override;

private:
	unsigned int y0;
};

