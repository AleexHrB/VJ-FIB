#pragma once
#include "Weapon.h"
#include <vector>
class DoubleHook : public Weapon
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	bool shoot(const glm::ivec2& pos) override;
	pair<glm::ivec2, glm::ivec2> getHitbox() override;
	void render() override;
	bool checkCollisionProj(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b) override;

private:
	unsigned int currentHooks = 0;
	unsigned int nextPlace = 0;
	unsigned int y0[2];
	vector<pair<glm::ivec2, Sprite*>> v;
	vector<bool> used = vector<bool>(4, false);
};

