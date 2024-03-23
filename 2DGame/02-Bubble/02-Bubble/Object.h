#pragma once
#include "Entity.h"
#include "Effects.h"

class Object : public Entity
{
public:
	void update(int deltaTime) override;
	virtual Effects applyEffect();

	unsigned int getBonus();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos);
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

private:
	float t = 0;
	Effects eff;
	Fruit f;
	void loadFruit();
	void loadPowerUp();
	glm::ivec2 initPos;
};

