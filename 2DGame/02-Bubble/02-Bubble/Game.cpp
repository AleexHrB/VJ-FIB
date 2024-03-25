#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene.init(0);
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if (key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	else if (key == GLFW_KEY_0)
		scene.init(0);
	else if (key == GLFW_KEY_1)
		scene.init(1);
	else if (key == GLFW_KEY_2)
		scene.init(2);
	else if (key == GLFW_KEY_3)
		scene.init(3);
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
	else if (key == GLFW_KEY_P)
		scene.treatPowerUp(Effects::SLOW);
	else if (key == GLFW_KEY_F)
		scene.treatPowerUp(Effects::GET_BONUS);
	else if (key == GLFW_KEY_H)
		scene.treatPowerUp(Effects::HOOK);
	else if (key == GLFW_KEY_G)
		scene.changeGodMode();

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

bool Game::getKey(int key) const
{
	return keys[key];
}



