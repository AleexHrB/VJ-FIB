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


void Scene::init(const string &level, bool menu)
{
	initShaders();
	map = TileMap::createTileMap(level, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	l = list<Bubble*>();
	l.push_back(new Bubble());
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	l.back()->init(texProgram, glm::ivec2(320, 320), glm::ivec2(-4, 0), glm::ivec2(48,40), l.back() -> BLUE);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//bubble->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	l.back()->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;
	
	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
	//if(!text.init("fonts/OpenSans-Bold.ttf"))
	//if(!text.init("fonts/DroidSerif.ttf"))
	cout << "Could not load font!!!" << endl;
	this -> menu = menu;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	for (Enemy* e : l_e) e->update(deltaTime);
	
	auto it = l.begin();
	while (it != l.end()) {
		Bubble* bub = *it;
		bub -> update(deltaTime);
		if (bub->circle_test(player->getPosition())) {
			cout << "hit" << endl;
			bool dead = player->substract_live();
			if (dead) {
				cout << "Game Over" << endl;
				exit(0);
			}
		}
		if (player -> hook_test(bub -> getPosition(), bub -> getSize()) && hitted()) {
			player->setShoot(false);
			
			if ((bub->getSize() / 2).x > 6) {
				glm::ivec2 bub_sp = bub->getSpeed();
				l.push_back(new Bubble());
				l.back()->init(texProgram, bub->getPosition(), bub_sp, bub->getSize() / 2, l.back() -> BLUE);
				l.back()->setTileMap(map);
				l.push_back(new Bubble());
				l.back()->init(texProgram, bub->getPosition(), glm::ivec2(-2 * bub_sp.x, bub_sp.y), bub->getSize() / 2, l.back()->BLUE);
				l.back()->setTileMap(map);
			}
			delete bub;
			it = l.erase(it);	
			l_e.push_back(new Enemy());
			l_e.back() -> init(texProgram, glm::ivec2(48,40), glm::ivec2(5, 0), glm::ivec2(32,32));

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
	if(!menu) player->render();
	for (Bubble* bub : l) bub->render();
	for (Enemy* e : l_e) e->render();
	if(!menu) text.render("Time: " + to_string(int(currentTime/1000)), glm::vec2(20, 460), 32, glm::vec4(1, 1, 1, 1));
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
	if (currentTime - inmuneTime > 100) {
		inmuneTime = currentTime;
		return true;
	}

	else return false;
}



