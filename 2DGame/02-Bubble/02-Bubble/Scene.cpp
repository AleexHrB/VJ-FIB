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
	lB = list<Bubble*>();
	lE = list<Enemy*>();
	srand(time(NULL));
	initShaders();
	this->level = level;
	string levelFile = "levels/level" + to_string(level) + ".txt";
	map = TileMap::createTileMap(levelFile, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);


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

	lB.push_back(new Bubble());
	if (menu) lB.back()->init(glm::ivec2(320, 320), texProgram, rn, Bubble::Size::MID, glm::ivec2(80, 80), glm::vec2(-8,0));
	else lB.back()->init(glm::ivec2(320, 120), texProgram, Bubble::Color::RED, Bubble::Size::BIG, glm::ivec2(80, 80), glm::vec2(-8, 0));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	lB.back()->setTileMap(map);

	
	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
	//if(!text.init("fonts/OpenSans-Bold.ttf"))
	//if(!text.init("fonts/DroidSerif.ttf"))
	cout << "Could not load font!!!" << endl;
	
	
	if (currentTime == 0.0f) {
		player = new Player();
		score = 0;
	
	}
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	currentTime = 0.0f;
	timeLimit = 100;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	for (auto itO = lO.begin(); itO != lO.end();) {
		Object* o = *itO;
		o->update(deltaTime);
		if (o->checkCollision(player->getHitbox())) {
			delete o;
			itO = lO.erase(itO);
		}
		else ++itO;
	}

	for (auto itE = lE.begin(); itE != lE.end();) {
		Enemy* e = *itE;
		e->update(deltaTime);
		if (e->checkCollision(player->getHitbox()) && hitted()) {
			bool dead = player->substractLive();
			if (dead) exit(0);
			else init(this->level);
			break;
		}

		else if (e->checkCollision(player->getWeaponHitbox())) {
			itE = lE.erase(itE);
			delete e;
			player->hitWeapon();
		}

		else ++itE;
	}

	for (auto itB = lB.begin(); itB != lB.end();) {
		Bubble* b = *itB;
		b->update(deltaTime);
		if (b->checkCollision(player->getHitbox()) && hitted()) {
			bool dead = player->substractLive();
			if (dead) exit(0);
			else init(this->level);
			break;
		}

		else if (b->checkCollision(player->getWeaponHitbox())) {
			Bubble::Size s = b->getSize();
			Bubble::Color c = b->getColor();
			player->hitWeapon();
			this->score += b->getBonus();
			
			if (s != Bubble::Size::TINY) {
				Bubble::Size next;

				switch (s) {
				case Bubble::BIG:
					next = Bubble::MID;
					break;
				case Bubble::MID:
					next = Bubble::SMALL;
					break;
				default:
					next = Bubble::TINY;
				}
				glm::vec2 speed = b->getSpeed();
				lB.push_back(new Bubble());
				lB.back()->init(glm::ivec2(320, 320), texProgram, c, next, b->getPosition(), speed);
				lB.back()->setTileMap(map);
				lB.push_back(new Bubble());
				lB.back() -> init(glm::ivec2(320, 320), texProgram, c, next, b->getPosition(), glm::vec2(-speed.x, speed.y));
				lB.back()->setTileMap(map);

				if (rand()% 2 == 0) {
					Enemy* next;
					if (rand() % 2 == 0) next = new Bird();
					else next = new Crab();
					lE.push_back(next);
					lE.back()->init(glm::ivec2(320, 320), texProgram);
					lO.push_back(new Object());
					lO.back()->init(glm::ivec2(320, 320), texProgram, Effects::STICK, b -> getPosition());
				}
			}

			delete b;
			itB = lB.erase(itB);
		}

		else ++itB;
	}


	if (!menu && int(currentTime / 1000) == timeLimit) {
		cout << "Game Over" << endl;
		exit(0);
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
	for (Bubble* b : lB) b->render();
	for (Enemy* e : lE) e->render();
	for (Object* o : lO) o->render();
	if(!menu) player->render();
	if (!menu) {
		string time = to_string(int(timeLimit - currentTime / 1000));
		if (int(timeLimit - currentTime / 1000) < 100 && int(timeLimit - currentTime / 1000) > 9) time = "0" + time;
		else if (currentTime != 100) time = "00" + time;
		text.render(("Time: " + time), glm::vec2(600, 48), 32, glm::vec4(1, 1, 1, 1));
		text.render("Score: " + to_string(score), glm::vec2(20, 440), 16, glm::vec4(1, 1, 1, 1));
		text.render("Lives: " + to_string(player -> getLives()), glm::vec2(20, 460), 16, glm::vec4(1, 1, 1, 1));
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



