#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "menu.h"



void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	SoundManager::instance().init();
	menu.init();
	SoundManager::instance().changeBgMusic("sounds/Main.mp3", true, false);
	inMenu = true;
	score = 0;
}

bool Game::update(int deltaTime)
{
	if (!inMenu)
		scene.update(deltaTime);
	else menu.update(deltaTime);

	for (int i = 0; i < GLFW_KEY_LAST + 1; ++i) {
		oldKeys[i] = keys[i];
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!inMenu)
		scene.render();
	else menu.render();
}

void Game::setLevel(int level)
{
	inMenu = false;
	scene.init(level);
}

void Game::keyPressed(int key)
{
	if (key == GLFW_KEY_0) {
	}
		
	else if (key == GLFW_KEY_1) {
		inMenu = false;
		scene.init(1);
	}
		
	else if (key == GLFW_KEY_2) {
		inMenu = false;
		scene.init(2);
	}
		
	else if (key == GLFW_KEY_3) {
		inMenu = false;
		scene.init(3);
	}
	else if (key == GLFW_KEY_T)
		scene.treatPowerUp(Effects::GUN);
	else if (key == GLFW_KEY_Y)
		scene.treatPowerUp(Effects::STICK);
	else if (key == GLFW_KEY_U)
		scene.treatPowerUp(Effects::DOUBLE);
	else if (key == GLFW_KEY_I)
		scene.treatPowerUp(Effects::DYNAMITE);
	else if (key == GLFW_KEY_O)
		scene.treatPowerUp(Effects::FREEZE);
	else if (key == GLFW_KEY_P) {
		scene.treatPowerUp(Effects::SLOW);
	}
	else if (key == GLFW_KEY_K) {
		scene.treatPowerUp(Effects::UNFREEZE);
	}
	else if (key == GLFW_KEY_Q) {
		scene.treatPowerUp(Effects::HOOK);
	}
	else if (key == GLFW_KEY_L) {
		scene.treatPowerUp(Effects::UNSLOW);
	}
	else if (key == GLFW_KEY_F)
		scene.treatPowerUp(Effects::GET_BONUS);
	else if (key == GLFW_KEY_H)
		scene.treatPowerUp(Effects::HOOK);
	else if (key == GLFW_KEY_G)
		scene.changeGodMode();
	else if (key == GLFW_KEY_ESCAPE) {
		menu.init();
		
		inMenu = true;
		scene.unload();
		score = 0;
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

int Game::getScore()
{
	return score;
}

void Game::addScore(int add)
{
	score += add;
}

void Game::setMenu()
{
	inMenu = true;
	menu.init();
	score = 0;
}

bool Game::getKeyUp(int key) const
{
	return keys[key] && !oldKeys[key];
}

bool Game::getKey(int key) const
{
	return keys[key];
}

void Game::resize(int w, int h)
{
	glViewport(0, 0, w, h);
}

