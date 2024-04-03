#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Menu.h"


#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 480
#define BLOCK_BONUS 200

// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void setLevel(int level);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	int getScore();
	void addScore(int add);
	void setMenu();
	void resize(int w, int h);
	
	bool getKeyUp(int key) const;
	bool getKey(int key) const;

private:
	bool bPlay; // Continue to play game?
	bool inMenu;
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
	bool oldKeys[GLFW_KEY_LAST + 1];
						    // we can have access at any time
	Scene scene;
	Menu menu;
	int score;

};


#endif // _GAME_INCLUDE


