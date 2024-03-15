#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene.init("levels/menu.txt");
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
		scene.init("levels/menu.txt");
	else if (key == GLFW_KEY_1)
		scene.init("levels/level00.txt");
	else if (key == GLFW_KEY_2)
		scene.init("levels/level01.txt");
	else if (key == GLFW_KEY_3)
		scene.init("levels/level02.txt");
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



