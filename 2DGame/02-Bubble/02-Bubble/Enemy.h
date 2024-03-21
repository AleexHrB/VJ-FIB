#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	virtual unsigned int getBonus() = 0;
};
