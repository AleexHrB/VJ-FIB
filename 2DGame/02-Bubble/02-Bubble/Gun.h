#pragma once
#include "Weapon.h"
#include <vector>
class Gun : public Weapon
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	bool shoot(const glm::ivec2& pos) override;
	pair<glm::ivec2, glm::ivec2> getHitbox() override;
	void render() override;
	void hitted() override;
	bool checkCollisionProj(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b) override;

private:
	unsigned int currentBullets = 0;
	unsigned int nextPlace = 0;
	float t = 0;
	Sprite* newBullet();
	vector<pair<glm::ivec2, Sprite*>> v;
	vector<bool> used = vector<bool>(4,false);
};

