#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"




#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 21


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
	lO = list<Object*>();
	srand(time(NULL));
	initShaders();
	this->level = level;
	string levelFile = "levels/level" + to_string(level) + ".txt";
	map = TileMap::createTileMap(levelFile, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//SoundManager::instance().changeBgMusic("sounds/8_bit_ballroom_dance.mp3", true, false);

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

	int n = map[0].getBubNumber();
	int* bubs = map[0].getBubData();
	for (int i = 0; i < n; ++i) {
		Bubble::Color col;
		switch (bubs[i + 2]) {
			case 0:
				col = Bubble::Color::BLUE;
				break;
			case 1:
				col = Bubble::Color::RED;
				break;
			case 2:
				col = Bubble::Color::GREEN;
				break;
		}

		Bubble::Size siz;
		switch (bubs[i + 3]) {
			case 0:
				siz = Bubble::Size::TINY;
				break;
			case 1:
				siz = Bubble::Size::SMALL;
				break;
			case 2:
				siz = Bubble::Size::MID;
				break;
			case 3:
				siz = Bubble::Size::BIG;
				break;
		}

		lB.push_back(new Bubble());
		lB.back()->init(glm::ivec2(0, 0), texProgram, col, siz, glm::ivec2(bubs[i], bubs[i + 1]), glm::vec2(10, 2));
		lB.back()->setTileMap(map);
	}

	//lB.push_back(new Bubble());
	//if (menu) lB.back()->init(glm::ivec2(320, 320), texProgram, rn, Bubble::Size::MID, glm::ivec2(340, 320), glm::vec2(8,2));
	//else lB.back()->init(glm::ivec2(320, 80), texProgram, Bubble::Color::RED, Bubble::Size::BIG, glm::ivec2(320, 32), glm::vec2(-8, 0));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);

	
	// Select which font you want to use
	if (!text.init("fonts/ArcadeClassic.ttf"))
	//if(!text.init("fonts/OpenSans-Bold.ttf"))
	//if(!text.init("fonts/DroidSerif.ttf"))
	cout << "Could not load font!!!" << endl;
	
	
	if (currentTime == 0.0f) {
		player = new Player();
	}

	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	player->changeWeapon(Effects::HOOK);
	player->update(2);

	currentTime = 0.0f;
	inmuneTime = currentTime;
	timeLimit = 100;
	freeze = false;

	UI.loadFromFile("images/PowerUpsMin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	liveSprite = Sprite::createSprite(glm::vec2(32,32), glm::vec2(1.0/6.0f, 1.0/3.0f), &UI, &texProgram);
	liveSprite->setNumberAnimations(1);
	liveSprite->setAnimationSpeed(0, 1);
	liveSprite->addKeyframe(0, glm::vec2(1.0f/3.0f, 2.0/3.0f));
	liveSprite->changeAnimation(0);

	liveSprite->setPosition(glm::vec2(20, 440));
	
	powerUp = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1 / 6.0f, 1 / 3.0f), &UI, &texProgram);
	powerUp->setNumberAnimations(3);
	powerUp->addKeyframe(0, glm::vec2(0.f, 0.f));
	powerUp->addKeyframe(1, glm::vec2(0.f, 1.0 /3.0f));
	powerUp->addKeyframe(2, glm::vec2(0.f, 2.0/3.0f));

	powerUp->setPosition(glm::vec2(240, 430));
	deathCountDown = -1;
	poweredUp = false;
	startTimer = READY_TIME;
	stageCompletedTimer = 0;

}

void Scene::update(int deltaTime)
{ 
	
	if (startTimer > 0 || stageCompletedTimer > 0) {
		startTimer -= deltaTime;
		if (startTimer < 0) startTimer = 0;
	
		if (stageCompletedTimer > 0) {
			stageCompletedTimer -= deltaTime;
			if (stageCompletedTimer <= 0) {
				stageCompletedTimer = 0;
				if (level == 3) {
					Game::instance().setMenu();
					return;
				}
				else this->init(level + 1);
			}
		}
		
	}
	if ((startTimer > 0 || stageCompletedTimer) && !menu) return;

	if (!freeze && deathCountDown == -1) currentTime += deltaTime;
	if (deathCountDown == 0) {
		if (player->getLives() == 0) {
			player->setLives(3);
			Game::instance().setMenu();
		}
		else init(this->level);
	}
	else if (deathCountDown > 0) --deathCountDown;
	player->update(deltaTime);
	updatePowerUps(deltaTime);
	for (auto itO = lO.begin(); itO != lO.end();) {
		Object* o = *itO;
		o->update(deltaTime);
		if (o->checkCollision(player->getHitbox())) {
			Game::instance().addScore(o->getBonus());
			Effects eff = o->applyEffect();
			powerUpTimers[eff] = 0.1;
			delete o;
			itO = lO.erase(itO);
			this -> treatPowerUp(eff);
		}
		else ++itO;
	}

	for (auto itE = lE.begin(); itE != lE.end();) {
		Enemy* e = *itE;
		if (!freeze && deathCountDown == -1) e->update(deltaTime);
		if (!godMode && e->checkCollision(player->getHitbox()) && !player -> isDisabled()) {
			player->setDisabled(true);
			player->changeWeapon(Effects::HOOK);
			poweredUp = false;
			break;
		}

		else if (player -> checkProjectileHitbox(e -> getHitbox(), nullptr)) {
			itE = lE.erase(itE);
			Game::instance().addScore(e -> getBonus());
			delete e;
			player->hitWeapon();
		}

		else ++itE;
	}

	for (auto itB = lB.begin(); itB != lB.end();) {
		Bubble* b = *itB;
		if (b->isDestroying() || (!freeze && deathCountDown == -1)) {
			if (slowed) b->update(deltaTime/2);
			else b->update(deltaTime);
		} 
		if (b->isDestroyed()) {
			delete b;
			itB = lB.erase(itB);
		}

		else if (!freeze && !godMode && b->checkCollision(player->getHitbox()) && hitted()) {
			bool dead = player->substractLive();
			freeze = false;
			slowed = false;
			deathCountDown = DEATH_FRAMES;
			SoundManager::instance().sound("sounds/damage.wav");
			break;
		}

		else if (!b ->isDestroying() && player->checkProjectileHitbox(b->getHitbox(), b)) {
			Bubble::Size s = b->getSize();
			Bubble::Color c = b->getColor();
			player->hitWeapon();
			if (s == this->lastSize) mult *= 2;
			else mult = 1;
			
			if (mult > 8) mult = 8;
			this->lastSize = s;
			Game::instance().addScore(mult * b->getBonus());
			
			
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
				lB.back()->init(glm::ivec2(320, 320), texProgram, c, next, b->getPosition() - glm::ivec2(5 * (4-s), 0), glm::vec2(speed.x, -15));
				lB.back()->setTileMap(map);
				lB.push_back(new Bubble());
				lB.back()->init(glm::ivec2(320, 320), texProgram, c, next, b->getPosition() + glm::ivec2(5 * (4-s), 0), glm::vec2(-speed.x, -15));
				lB.back()->setTileMap(map);

				if (rand() % 5 == 0) {
					Enemy* next;
					if (rand() % 2 == 0) next = new Bird();
					else next = new Crab();
					lE.push_back(next);
					lE.back()->init(glm::ivec2(320, 320), texProgram);
				}
				if (rand()% 3 == 0) {
					lO.push_back(new Object());
					lO.back()->init(glm::ivec2(320, 320), texProgram, b -> getPosition());
					lO.back()->setTileMap(map);
				}
			}
			SoundManager::instance().sound("sounds/Pop.mp3");
			b -> destroy();
			
		}

		else ++itB;
	}

	
	if (!menu && int(currentTime / 1000) == timeLimit && deathCountDown == -1) {
		bool dead = player->substractLive();
		freeze = false;
		slowed = false;
		deathCountDown = DEATH_FRAMES;
		SoundManager::instance().sound("sounds/damage.mp3");
	}

	if (!menu && lB.size() == 0) {
		stageCompletedTimer = STAGE_CLEAR_TIME;
		Game::instance().addScore(int(timeLimit - currentTime / 1000)*20);
		SoundManager::instance().changeBgMusic("sounds/victory.mp3", false, false);
	}
	map->update(deltaTime);

	/*if (Game::instance().getKey(GLFW_KEY_T) && (powerUp->animation() != 0 || !poweredUp)) {
		poweredUp = true;
		powerUp->changeAnimation(0);
		player->changeWeapon(Effects::STICK);
	}
	else if (Game::instance().getKey(GLFW_KEY_Y) && (powerUp->animation() != 1 || !poweredUp)) {
		poweredUp = true;
		powerUp->changeAnimation(1);
		player->changeWeapon(Effects::DOUBLE);
	}
	else if (Game::instance().getKey(GLFW_KEY_U) && (powerUp->animation() != 2 || !poweredUp)) {
		poweredUp = true;
		powerUp->changeAnimation(2);
		player->changeWeapon(Effects::GUN);
	}
	else if (Game::instance().getKey(GLFW_KEY_Q) && (poweredUp)) {
		poweredUp = false;
		powerUp->changeAnimation(0);
		player->changeWeapon(Effects::HOOK);
	}*/
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
	if (!menu) {
		if (poweredUp) powerUp->render();
		bool flicker = (currentTime - inmuneTime <= 1500 && startTimer <= 0);
		glm::vec4 color;
		if (godMode) color = glm::vec4(0.5,1,0.5,1);
		else if(player->isDisabled()) color = glm::vec4(1, 0.5, 0.25, 1);
		else color = glm::vec4(1, 1, 1, 1);
		player->render(flicker, color);
		int lives = player->getLives();
		for (int i = 0; i < lives; ++i) {
			liveSprite->setPosition(glm::vec2(20 + 32*i, 440));
			liveSprite->render();
		}
		
		
		string time = to_string(int(timeLimit - currentTime / 1000));
		if (int(timeLimit - currentTime / 1000) >= 100) time = time;
		else if (int(timeLimit - currentTime / 1000) < 100 && int(timeLimit - currentTime / 1000) > 9) time = "0" + time;
		else time = "00" + time;
		text.render(("Time  " + time), glm::vec2(560, 48), 32, glm::vec4(1, 1, 1, 1));
		text.render("Score  " + to_string(Game::instance().getScore()), glm::vec2(20, 430), 16, glm::vec4(1, 1, 1, 1));
		text.render("Level " + to_string(level), glm::vec2(320, 450), 32, glm::vec4(1, 1, 1, 1));
		if (startTimer > 0) text.render("READY", glm::vec2(256, 240), 64, glm::vec4(1,1,1,1));
		if (stageCompletedTimer > 0) text.render("STAGE CLEAR", glm::vec2(160, 240), 64, glm::vec4(1, 1, 1, 1));
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




void Scene::explodeBubbles()
{

	unsigned int size = lB.size();
	unsigned int i = 0;
	list<Bubble*>::iterator itB = lB.begin();

	while (itB != lB.end()) {
		Bubble* b = *itB;
		int s = b->getSize();
		if (!b->isDestroying() && !b->isDestroyed() && s != Bubble::Size::TINY) {
			Bubble::Color c = b->getColor();
			auto speed = b->getSpeed();
			
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

			lB.push_back(new Bubble());
			lB.back()->init(glm::ivec2(320, 320), texProgram, c, next, b->getPosition() - glm::ivec2(5 * (4 - s), 0), glm::vec2(speed.x, -15));
			lB.back()->setTileMap(map);
			lB.push_back(new Bubble());
			lB.back()->init(glm::ivec2(320, 320), texProgram, c, next, b->getPosition() + glm::ivec2(5 * (4 - s), 0), glm::vec2(-speed.x, -15));
			lB.back()->setTileMap(map);

			SoundManager::instance().sound("sounds/Pop.mp3");
			b->destroy();
			//delete b;
			//itB = lB.erase(itB);
		}
		
		++itB;
	}
}

inline bool Scene::hitted()
{
	if (currentTime - inmuneTime > 1500) {
		inmuneTime = currentTime;
		return true;
	}

	else return false;
}

void Scene::updatePowerUps(int deltaTime)
{
	for (unsigned int i = 0; i < Effects::SIZE_EFF; ++i) {

		if (powerUpTimers[i] > 0) {
			powerUpTimers[i] += deltaTime / 100.0;
			if (powerUpTimers[i] > 100) {
				powerUpTimers[i] = 0;
				switch (Effects(i)) {
				case Effects::GUN:
					player->changeWeapon(Effects::HOOK);
					poweredUp = false;
					break;
				case Effects::STICK:
					player->changeWeapon(Effects::HOOK);
					poweredUp = false;
					break;
				case Effects::DOUBLE:
					player->changeWeapon(Effects::HOOK);
					poweredUp = false;
					break;
				case Effects::HOOK:
					player->changeWeapon(Effects::HOOK);
					poweredUp = false;
					break;
				case Effects::FREEZE:
					freeze = false;
					break;
				case Effects::SLOW:
					slowed = false;
					//for (Bubble* b : lB) b->changeGravity(1.8f);
					break;
				default:
					break;
				}
			}
		}
	}
}


void Scene::treatPowerUp(Effects f)
{
	switch (f) {
	case Effects::GUN:
		player->changeWeapon(f);
		poweredUp = true;
		powerUp->changeAnimation(2);
		SoundManager::instance().sound("sounds/pickupWeapon.wav");
		break;
	case Effects::STICK:
		player->changeWeapon(f);
		poweredUp = true;
		powerUp->changeAnimation(0);
		SoundManager::instance().sound("sounds/pickupWeapon.wav");
		break;
	case Effects::DOUBLE:
		player->changeWeapon(f);
		powerUp->changeAnimation(1);
		SoundManager::instance().sound("sounds/pickupWeapon.wav");
		poweredUp = true;
		break;
	case Effects::HOOK:
		poweredUp = false;
		player->changeWeapon(f);
		break;
	case Effects::DYNAMITE:
		this->explodeBubbles();
		SoundManager::instance().sound("sounds/dinamita.mp3");
		break;
	case Effects::FREEZE:
		freeze = true;
		SoundManager::instance().sound("sounds/clock.mp3");
		break;
	case Effects::SLOW:
		slowed = true;
		SoundManager::instance().sound("sounds/clock.mp3");
		//for (Bubble* b : lB) b->changeGravity(1.0f);
		break;
	case Effects::UNFREEZE:
		freeze = false;
		break;

	case Effects::UNSLOW:
		slowed = false;
		break;
	default:
		Game::instance().addScore(0);
		break;
	}
}

void Scene::changeGodMode()
{
	godMode = !godMode;
}

void Scene::unload()
{
	this->menu = 0;
	//SoundManager::instance().changeBgMusic(nullptr, false, false);
}

