#pragma once
#include "ShaderProgram.h"
#include "Text.h"
#include "Scene.h"


enum Scenes {
	MAIN_MENU, HOW_TO_PLAY_OBJECTIVE, HOW_TO_PLAY_POWER_UPS, HOW_TO_PLAY_ENEMIES, HOW_TO_PLAY_SORROUNDING, CREDITS, END, SIZE
};

struct TextInfo {
	string text;
	glm::ivec2 pos;
	int textSize;
};

class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

	void theEnd();

private:
	void initShaders();
	void changeHowToPlay();

	Texture bgMenuSheet, bgHowToPlaySheet, bgCreditsSheet;

	vector<vector<TextInfo>> texts;

	Text titleObj;
	Text textObj;

	ShaderProgram program;
	glm::mat4 projection;
	int scene;
	int selected;
	glm::vec2 backgroundSize;
	GLuint bVao;
	GLuint bVbo;
	GLint backPosLocation, backTexCoordLocation;


	ISoundEngine* engine;
	ISoundSource* menuNavSrc;
};

