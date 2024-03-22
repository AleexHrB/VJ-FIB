#pragma once
#include "Entity.h"
#include "Effects.h"

class Object : public Entity
{
public:
	void update(int deltaTime) override;
	virtual Effects applyEffect();

	unsigned int getBonus();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Effects f, const glm::vec2& pos);
	pair<glm::ivec2, glm::ivec2> getHitbox() override;
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

private:
	float t = 0;
	Effects f;
	void loadFruit();
	void loadPowerUp();
};

