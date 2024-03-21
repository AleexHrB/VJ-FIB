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
	unsigned int getBonus() override;
};