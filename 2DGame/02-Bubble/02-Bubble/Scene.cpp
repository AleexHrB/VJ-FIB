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


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level00.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	l.push_back(new Bubble());
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	l.back()->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::ivec2(20, 50), glm::ivec2(4, 0));
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//bubble->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	l.back()->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	
	auto it = l.begin();
	while (it != l.end()) {
		Bubble* bub = *it;
		bub -> update(deltaTime);
		if (bub->circle_test(player->getPosition()) && hitted()) {
			cout << "hit" << endl;
			bool dead = player->substract_live();
			if (dead) {
				cout << "Game Over" << endl;
				exit(0);
			}
		}
		if (player -> hook_test(bub -> getPosition()) && hitted()) {
			l.push_back(new Bubble());
			glm::ivec2 bub_sp = bub->getSpeed();
			l.back()->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, bub -> getPosition(), bub_sp);
			l.back()->setTileMap(map);
			l.push_back(new Bubble());
			l.back()->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, bub->getPosition(), glm::ivec2(-bub_sp.x, bub_sp.y));
			l.back()->setTileMap(map);
			delete bub;
			it = l.erase(it);
			player->setShoot(false);
		}
		else ++it;
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
	player->render();
	for (Bubble* bub : l) bub->render();
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
	if (currentTime - inmuneTime > 1000) {
		inmuneTime = currentTime;
		return true;
	}

	else return false;
}



