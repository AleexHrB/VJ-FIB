#pragma once
#include "Entity.h"
#include "Bubble.h"

class Weapon : public Entity
{
public: 
	virtual bool shoot(const glm::ivec2& pos) = 0;
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	void render() override {
		if (shooted) sprite->render();
	};
	virtual void hitted() {
		shooted = false;
	}

	virtual bool checkCollisionProj(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b) {
		if (!shooted) return false;

		if (b == nullptr) return this->checkCollision(hitbox);
		else return b->checkCollision(getHitbox());
	}
protected:
	bool shooted = false;
};

