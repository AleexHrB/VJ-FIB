#pragma once

#include "Object.h"

class Fruit : public Object
{
public:
	enum FruitType {
		CHERRY,
		LEMON,
		BANNANA,
		ORANGE,
		WATERMELON,
		PINEAPPLE,
		GRAPES,
		APPLE,
		STRAWBERRY,
		MELON
	};
	
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, FruitType f, const glm::vec2& pos);
	unsigned int getBonus() override;
	Effects applyEffect() override;

	private
		FruitType f;

};