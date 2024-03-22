#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Entity
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render();
	glm::ivec2 getPosition();
	void setPosition(const glm::ivec2& pos);
	void setTileMap(TileMap* tileMap);
	virtual pair<glm::ivec2, glm::ivec2> getHitbox();
	virtual bool checkCollision(const pair<glm::ivec2, glm::ivec2>& hitbox);
	glm::ivec2 getSpeed();
	void setSpeed(const glm::ivec2& s);

protected:
	glm::ivec2 tileMapDispl, position, sizeQuad, speed;
	Texture spritesheet;
	ShaderProgram texProgram;
	Sprite* sprite;
	TileMap* map;
	float g = 1.8;
};

