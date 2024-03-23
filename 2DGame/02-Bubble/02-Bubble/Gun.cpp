#include "Gun.h"
#include <iostream>
enum Anims {
	EXPAND,
	NOT_EXPAND,
	SIZE
};
void Gun::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Gun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->texProgram = shaderProgram;
	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
	//sprite->setPosition(this -> position);

	sprite->setNumberAnimations(SIZE);

	sprite->setAnimationSpeed(EXPAND, 2);
	sprite->addKeyframe(EXPAND, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(NOT_EXPAND, 2);
	sprite->addKeyframe(NOT_EXPAND, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(NOT_EXPAND);
	v = vector<pair<glm::ivec2, Sprite*>>(4);
	for (unsigned int i = 0; i < 4; ++i) v[i] = { glm::ivec2(-1,-1), nullptr };
}

void Gun::update(int deltaTime)
{
	t += deltaTime / 100.0;
	for (unsigned int i = 0; i < v.size(); ++i) {
		if (!used[i]) continue;

		if (v[i].first.y > 16) {
			v[i].first.y -= 8;
			if (t > 1) {
				t = 0;
				v[i].second ->changeAnimation(NOT_EXPAND);
			}
			else v[i].second ->changeAnimation(EXPAND);
			v[i].second ->setPosition(glm::vec2(v[i].first));
		}
		else {
			used[i] = false;
			--currentBullets;
		}
	}
}

void Gun::shoot(const glm::ivec2& pos)
{
	if (currentBullets < 4) {
		v[nextPlace] = {pos, this -> newBullet()};
		used[nextPlace] = true;
		++currentBullets;
		nextPlace = (nextPlace+1) % 4;
	}
}

pair<glm::ivec2, glm::ivec2> Gun::getHitbox()
{
	pair<glm::ivec2, glm::ivec2> p = { glm::ivec2(20,20), glm::ivec2(position.x, position.y) };
	pair<glm::ivec2, glm::ivec2> p2 = { glm::ivec2(-1,-1), glm::ivec2(-1,-1) };
	return shooted ? p : p2;
}

void Gun::render()
{
	for (unsigned int i = 0; i < v.size(); ++i) if (used[i]) v[i].second->render();
}

bool Gun::checkCollisionProj(const pair<glm::ivec2, glm::ivec2>& hitbox, Bubble* b)
{

	for (unsigned int i = 0; i < v.size(); ++i) {

		if (used[i]) {

			bool check = false;
			pair<glm::ivec2, glm::ivec2> p = { glm::ivec2(20,20) , v[i].first };
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

Sprite* Gun::newBullet()
{
	Sprite* s;
	spritesheet.loadFromFile("images/Gun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	s = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.5f, 1.0f), &spritesheet, &texProgram);
	//sprite->setPosition(this -> position);

	s->setNumberAnimations(SIZE);

	s->setAnimationSpeed(EXPAND, 2);
	s->addKeyframe(EXPAND, glm::vec2(0.0f, 0.0f));

	s->setAnimationSpeed(NOT_EXPAND, 2);
	s->addKeyframe(NOT_EXPAND, glm::vec2(0.5f, 0.f));

	s->changeAnimation(NOT_EXPAND);
	return s;
}
