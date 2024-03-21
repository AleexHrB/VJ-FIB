#pragma once
#include "Entity.h"

class Object : public Entity
{
	void update(int deltaTime) override;
	enum Effects {
		GET_BONUS
	};
	virtual Effects applyEffect();

	virtual unsigned int getBonus() = 0;
};

