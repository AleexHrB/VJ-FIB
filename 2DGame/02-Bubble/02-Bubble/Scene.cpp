#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 20


Scene::Scene()
{
	map = NULL;
	player = NULL;
}


Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init(unsigned int level)
{
	this->menu = level == 0;
	srand(time(NULL));
	initShaders();
	this->level = level;
	string levelFile = "levels/level" + to_string(level) + ".txt";
	map = TileMap::createTileMap(levelFile, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	l = list<Bubble*>();
	l_e = list<Enemy*>();
	l_f = list<Fruit*>();
	l_p = list<PowerUp*>();
	l.push_back(new Bubble());
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	Bubble::Color rn;
	switch (rand()%3)
	{
	case 0:
		rn = Bubble::Color::BLUE;
		break;
	case 1:
		rn = Bubble::Color::RED;
		break;
	case 2:
		rn = Bubble::Color::GREEN;
		break;
	}

	if (menu) l.back()->init(texProgram, glm::ivec2(320, 320), glm::ivec2(-8, 0), rn, l.back() -> MIDDLE);
	else l.back()->init(texProgram, glm::ivec2(320, 120), glm::ivec2(-8, 0), l.back()->BLUE, l.back()->BIG);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//bubble->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	l.back()->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);

	
	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
	//if(!text.init("fonts/OpenSans-Bold.ttf"))
	//if(!text.init("fonts/DroidSerif.ttf"))
	cout << "Could not load font!!!" << endl;
	
	
	if (currentTime == 0.0f) {
		score = 0;
	}
	currentTime = 0.0f;
	timeLimit = 100;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	auto itt = l_e.begin();
	while (itt != l_e.end()) {
		Enemy* e = *itt;
		e->update(deltaTime);
		if (e->getPosition().x > 760) {
			delete e;
			itt = l_e.erase(itt);
		}
		else ++itt;
	}

	auto itf = l_f.begin();
	while (itf != l_f.end()) {
		Fruit* f = *itf;
		if (f->getPosition().y <= 384)f->update(deltaTime);
		++itf;
	}

	auto itp = l_p.begin();
	while (itp != l_p.end()) {
		PowerUp* p = *itp;
		if (p->getPosition().y <= 368)p->update(deltaTime);
		++itp;
	}
	
	auto it = l.begin();
	while (it != l.end()) {
		Bubble* bub = *it;
		bub -> update(deltaTime);
		if (!menu && hitCircle(bub -> getHitboxBubble(), player -> getHitboxPlayer()) && hitted()) {
			bool dead = player->substract_live();
			if (dead) {
				cout << "Game Over" << endl;
				exit(0);
			}

			else {
				init(this->level);
				break;
			}
		}
		if (!menu && hitCircle(bub -> getHitboxBubble(), player -> getHitboxHook())) {
			player->setShoot(false);
			
			if (bub -> getSize() != bub -> TINY) {
				glm::ivec2 bub_sp = bub->getSpeed();
				l.push_back(new Bubble());
				l.back()->init(texProgram, bub->getPosition(), bub_sp, l.back() -> BLUE, bub -> getNextSize());
				l.back()->setTileMap(map);
				l.push_back(new Bubble());
				l.back()->init(texProgram, bub->getPosition(), glm::ivec2(-bub_sp.x, bub_sp.y), l.back()->BLUE, bub->getNextSize());
				l.back()->setTileMap(map);
				
			}
			Bubble::Size s = bub -> getSize();
			switch (s)
			{
			case Bubble::BIG:
				score += 50;
				break;
			case Bubble::MIDDLE:
				score += 100;
				break;
			case Bubble::SMALL:
				score += 150;
				break;
			case Bubble::TINY:
				score += 200;
				break;
			case Bubble::NONE:
				break;
			}

			int rng = rand() % 7;
			if (rng == 0) {
				l_e.push_back(new Enemy());
				l_e.back()->init(texProgram, glm::ivec2(0, 370), glm::ivec2(10, 0), glm::ivec2(32, 32));
			}
			else if (rng == 1) {
				l_f.push_back(new Fruit());
				l_f.back()->init(texProgram, glm::ivec2(384, 16), glm::ivec2(0, 10), glm::ivec2(16, 16), Fruit::FruitType::BANNANA);
			}
			else if (rng == 2) {
				l_f.push_back(new Fruit());
				l_f.back()->init(texProgram, glm::ivec2(384, 16), glm::ivec2(0, 10), glm::ivec2(16, 16), Fruit::FruitType::WATERMELON);
			}
			else if (rng == 3) {
				l_p.push_back(new PowerUp());
				l_p.back()->init(texProgram, bub->getPosition(), glm::ivec2(0, 10), glm::ivec2(32, 32), PowerUp::PowerUpType::PISTOL);
			}
			else if (rng == 4) {
				l_p.push_back(new PowerUp());
				l_p.back()->init(texProgram, bub->getPosition(), glm::ivec2(0, 10), glm::ivec2(32, 32), PowerUp::PowerUpType::DOUBLEHOOK);
			}
			else if (rng == 5) {
				l_p.push_back(new PowerUp());
				l_p.back()->init(texProgram, bub ->getPosition(), glm::ivec2(0, 10), glm::ivec2(32, 32), PowerUp::PowerUpType::STICKYHOOK);
			}

			delete bub;
			it = l.erase(it);	
			
			
		}
		else ++it;
	}
	if (!menu &&  l.size() == 0) {
		score += 1000;
		this->init((level%3) + 1);
	}
	if (!menu && int(currentTime / 1000) == timeLimit) {
		cout << "Game Over" << endl;
		exit(0);
	}

	for (auto it_f = l_f.begin(); !menu && it_f != l_f.end();) {
		Fruit* f = *it_f;
		if (hitRectangle(player->getHitboxPlayer(), f->getHitboxFruit())) {
			score += f->getBonus();
			delete f;
			it_f = l_f.erase(it_f);
		}

		else ++it_f;
	}

	for (auto it_e = l_e.begin(); !menu && it_e != l_e.end();) {
		Enemy *e = *it_e;
		if (hitRectangle(player->getHitboxPlayer(), e->getHitboxEnemy())) {
			delete e;
			it_e = l_e.erase(it_e);
			bool dead = player->substract_live();
			if (dead) {
				cout << "Game Over" << endl;
				exit(0);
			}

			else {
				init(this->level);
				break;
			}
		}

		else ++it_e;
	}
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	if(!menu) player->render();
	for (Bubble* bub : l) bub->render();
	for (Enemy* e : l_e) e->render();
	for (Fruit* f : l_f) f->render();
	for (PowerUp* p : l_p) p->render();
	if (!menu) {
		string time = to_string(int(timeLimit - currentTime / 1000));
		if (int(timeLimit - currentTime / 1000) < 100 && int(timeLimit - currentTime / 1000) > 9) time = "0" + time;
		else if (currentTime != 100) time = "00" + time;
		text.render(("Time: " + time), glm::vec2(600, 48), 32, glm::vec4(1, 1, 1, 1));
		text.render("Score: " + to_string(score), glm::vec2(20, 440), 16, glm::vec4(1, 1, 1, 1));
		text.render("Lives: " + to_string(player -> get_lives()), glm::vec2(20, 460), 16, glm::vec4(1, 1, 1, 1));
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


inline bool Scene::hitted()
{
	if (currentTime - inmuneTime > 500) {
		inmuneTime = currentTime;
		return true;
	}

	else return false;
}

//Source: GeeksForGeeks
inline bool Scene::hitRectangle(const pair<glm::ivec2, glm::ivec2>& r1, const pair<glm::ivec2, glm::ivec2>& r2)
{
	glm::ivec2 l1 = r1.second;
	glm::ivec2 rr1 = l1 + r1.first;
	glm::ivec2 l2 = r2.second;
	glm::ivec2 rr2 = l2 + r2.first;

	if (rr1.x < l2.x || rr2.x < l1.x) return false;
	if (rr1.y < l2.y || rr2.y < l1.y) return false;
	return true;
}

//Source: https://algo.monster/liteproblems/1401
inline bool Scene::hitCircle(const pair<glm::ivec2, glm::ivec2>& c, const pair<glm::ivec2, glm::ivec2>& r1)
{
	int deltaX = getMinimumDistance(r1.second.x, r1.second.x + r1.first.x, (c.second + c.first / 2).x);
	int deltaY = getMinimumDistance(r1.second.y, r1.second.y + r1.first.y, (c.second + c.first / 2).y);

	return deltaX * deltaX + deltaY * deltaY <= c.first.x * c.first.x / 4;
}



