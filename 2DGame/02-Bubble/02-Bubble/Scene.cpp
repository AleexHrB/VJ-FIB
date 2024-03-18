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
	for (Bubble* b : l) delete b;
	l = list<Bubble*>();
	l_e = list<Enemy*>();
	l.push_back(new Bubble());
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	if (menu) l.back()->init(texProgram, glm::ivec2(320, 320), glm::ivec2(-4, 0), l.back() -> BLUE, l.back() -> BIG);
	else l.back()->init(texProgram, glm::ivec2(320, 120), glm::ivec2(-4, 0), l.back()->BLUE, l.back()->BIG);
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
	
	score = 0;
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
		if (player -> hook_test(bub -> getPosition(), bub -> getSizeV()) ) {
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
			score += 4*(bub -> getSizeV().x);
			delete bub;
			it = l.erase(it);	
			if (rand() % 7 == 0) {
				l_e.push_back(new Enemy());
				l_e.back()->init(texProgram, glm::ivec2(0, 370), glm::ivec2(10, 0), glm::ivec2(32, 32));
			}
			
		}
		else ++it;
	}
	if (l.size() == 0) {
		score += 1000;
		this->init((level%3) + 1);
	}
	if (int(currentTime / 1000) == timeLimit) {
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
	if(!menu) player->render();
	for (Bubble* bub : l) bub->render();
	for (Enemy* e : l_e) e->render();
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

inline bool Scene::hitRectangle(const pair<glm::ivec2, glm::ivec2>& r1, const pair<glm::ivec2, glm::ivec2>& r2)
{
	
}

inline bool Scene::hitCircle(const pair<glm::ivec2, glm::ivec2>& c, const pair<glm::ivec2, glm::ivec2>& r1)
{
	return false;
}



