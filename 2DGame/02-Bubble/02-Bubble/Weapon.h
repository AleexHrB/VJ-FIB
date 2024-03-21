#pragma once
#include "Entity.h"

class Weapon : public Entity
{
public: 
	virtual void shoot(const glm::ivec2& pos) = 0;
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	void render() override {
		if (shooted) sprite->render();
	};

protected:
	bool shooted = false;
};

