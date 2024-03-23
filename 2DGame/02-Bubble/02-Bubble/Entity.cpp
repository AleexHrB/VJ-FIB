#include "Entity.h"

void Entity::render()
{
	sprite->render();
}

glm::ivec2 Entity::getPosition()
{
	return this -> position;
}

void Entity::setPosition(const glm::ivec2& pos)
{
	this->position = pos;
}

void Entity::setTileMap(TileMap* tileMap)
{
	this -> map = tileMap;
}

pair<glm::ivec2, glm::ivec2> Entity::getHitbox()
{
	return {sizeQuad, position};
}

bool Entity::checkCollision(const pair<glm::ivec2, glm::ivec2>& hitbox)
{
	glm::ivec2 l1 = getHitbox().second;
	glm::ivec2 rr1 = l1 + getHitbox().first;
	glm::ivec2 l2 = hitbox.second;
	glm::ivec2 rr2 = l2 + hitbox.first;

	if (rr1.x < l2.x || rr2.x < l1.x) return false;
	if (rr1.y < l2.y || rr2.y < l1.y) return false;
	return true;
}

glm::ivec2 Entity::getSpeed()
{
	return this -> speed;
}

void Entity::setSpeed(const glm::ivec2& s)
{
	this->speed = s;
}
