#include "DoubleHook.h"
#include <iostream>

void DoubleHook::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	this->texProgram = shaderProgram;
	spritesheet.loadFromFile("images/hook.png", TEXTURE_PIXEL_FORMAT_RGBA);
	v = vector<pair<glm::ivec2, Sprite*>>(2);
	for (unsigned int i = 0; i < v.size(); ++i) v[i] = { glm::ivec2(-1,-1), nullptr };
}

void DoubleHook::update(int deltaTime)
{
	for (unsigned int i = 0; i < v.size(); ++i) {
		if (!used[i]) continue;
		if (!map->collisionMoveUp(v[i].first, glm::ivec2(9, y0[i] - v[i].first.y), &v[i].first.y)) {
			v[i].first.y -= 4;
			v[i].second = Sprite::createSprite(glm::ivec2(9, y0[i] - v[i].first.y), glm::vec2(1.0f, (y0[i] - v[i].first.y) / 188.0), &spritesheet, &texProgram);
			v[i].second ->setPosition(v[i].first);
		}
		else {
			used[i] = false;
			--currentHooks;
			map->hookColision(v[i].first, glm::ivec2(9, y0[i] - v[i].first.y));
		}
	}
}

bool DoubleHook::shoot(const glm::ivec2& pos)
{
	if (currentHooks < 2) {
		y0[nextPlace] = pos.y + 32;
		v[nextPlace] = { pos, Sprite::createSprite(glm::ivec2(9, y0[nextPlace] - pos.y), glm::vec2(1.0f, (y0[nextPlace] - pos.y) / 188.0), &spritesheet, &texProgram) };
		used[nextPlace] = true;
		++currentHooks;
		nextPlace = (nextPlace+1)%2;
		return true;
	}
	return false;
}

pair<glm::ivec2, glm::ivec2> DoubleHook::getHitbox()
{
	pair<glm::ivec2, glm::ivec2> p = { glm::ivec2(20,20), glm::ivec2(position.x, position.y) };
	pair<glm::ivec2, glm::ivec2> p2 = { glm::ivec2(-1,-1), glm::ivec2(-1,-1) };
	return shooted ? p : p2;
}

void DoubleHook::hitted()
{
	shooted = false;
	currentHooks = 0;
	for (unsigned int i = 0; i < v.size(); ++i) used[i] = false;
}

void DoubleHook::render()
{
	for (unsigned int i = 0; i < v.size(); ++i) if (used[i]) v[i].second->render();
}

bool DoubleHook::checkCollisionProj(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b)
{

	for (unsigned int i = 0; i < v.size(); ++i) {

		if (used[i]) {

			bool check = false;
			pair<glm::ivec2, glm::ivec2> p = { glm::ivec2(9, y0[i] - v[i].first.y) , v[i].first };
			if (b != nullptr) check = b->checkCollision(p);
			else {
				glm::ivec2 l1 = p.second;
				glm::ivec2 rr1 = l1 + p.first;
				glm::ivec2 l2 = hitbox.second;
				glm::ivec2 rr2 = l2 + hitbox.first;

				if (rr1.x < l2.x || rr2.x < l1.x) continue;
				if (rr1.y < l2.y || rr2.y < l1.y) continue;
				check = true;
			}


			if (check) {
				used[i] = false;
				return true;
			}
		}
	}
	return false;
}
