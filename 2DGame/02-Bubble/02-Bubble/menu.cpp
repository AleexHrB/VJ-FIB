#include "Menu.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Menu::Menu()
{
	scene = 0;
	selected = 0;
}

Menu::~Menu()
{
}

void Menu::init()
{
	scene = 0;
	selected = 0;
	backgroundSize = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	textObj.init("fonts/PixelFont.ttf");
	titleObj.init("fonts/AncientModernTales.otf");

	initShaders();

	texts.resize(SIZE);

	texts[MAIN_MENU] = {
		{"PLAY", glm::ivec2(SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT / 2 + 35), 16},
		{"HOW TO PLAY", glm::ivec2(SCREEN_WIDTH / 2 - 88, SCREEN_HEIGHT / 2 + 85), 16},
		{"CREDITS", glm::ivec2(SCREEN_WIDTH / 2 - 56, SCREEN_HEIGHT / 2 + 135), 16},
		{"EXIT", glm::ivec2(SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT / 2 + 185), 16}
	};


	texts[HOW_TO_PLAY_OBJECTIVE] =
	{
		{"OBJECTIVE AND CONTROLS", glm::ivec2(SCREEN_WIDTH / 2 - 176, 50), 16},
		{"The goal of the game is to destroy all the bubbles!", glm::ivec2(40, 140), 10},
		{"Use the arrow keys to move arround, and press c to shoot your", glm::ivec2(40, 160), 10},
		{"weapon!", glm::ivec2(40, 180), 10},
		{"If you get hit by a bubble or the time runs out, you will", glm::ivec2(40, 200), 10},
		{"Lose a live", glm::ivec2(40, 220), 10},
		{"Try to complete the stage as quick as posible!", glm::ivec2(40, 240), 10},
		{"To test, you can use the numbers (1,2,3,...) to switch ", glm::ivec2(40, 260), 10},
		{"between levels, G to activate God mode and the keys T,Y,U,I,", glm::ivec2(40, 280), 10},
		{"O and P To activate powerUps (Gun, Sticky, Double hook, ", glm::ivec2(40, 300), 10},
		{"dynamite, freeze and slow). Keys K and L revert ", glm::ivec2(40, 320), 10},
		{"the effects of freeze and slow", glm::ivec2(40, 340), 10},
		{">", glm::ivec2(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50), 64}
	};

	texts[HOW_TO_PLAY_POWER_UPS] =
	{
		{"POWER UPS", glm::ivec2(SCREEN_WIDTH / 2 - 72, 50), 16},
		{"Bubbles will sometimes drop powerUps or fruits when destroyed", glm::ivec2(40, 120), 10},
		{"There are multiple power ups that will aid you!", glm::ivec2(40, 140), 10},
		{"Gun: The gun tranforms your weapon into a gun, with it you ", glm::ivec2(40, 160), 10},
		{"can shoot up to 4 bullets!!", glm::ivec2(40, 180), 10},
		{"Sticky Hook: Sticky hook sticks to the ceiling", glm::ivec2(40, 200), 10},
		{"Double Hook: Double hook allows you to shoot two hooks", glm::ivec2(40, 220), 10},
		{"Clock: This powerUP freezes, bubbles, enemies and even time!", glm::ivec2(40, 240), 10},
		{"Sand Clock: This powerUP slows down every bubbles", glm::ivec2(40, 260), 10},
		{"Dynamite: Dynamite pops every bubble until they reach the ", glm::ivec2(40, 280), 10},
		{"minimum size", glm::ivec2(40, 300), 10},
		{"Fruits: Pick up fruits to increase your score!", glm::ivec2(40, 320), 10},
		{ "<", glm::ivec2(50, SCREEN_HEIGHT - 50), 64 },
		{">", glm::ivec2(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50), 64}
	};

	texts[HOW_TO_PLAY_ENEMIES] =
	{
		{"ENEMIES AND BONUSES", glm::ivec2(SCREEN_WIDTH / 2 - 152, 50), 16},
		{"Somtimes, enemies may appear!", glm::ivec2(40, 120), 10},
		{"If an enemy hits you, you will lose your active powerUP and", glm::ivec2(40, 140), 10},
		{"you will alse be unable to shoot for a while", glm::ivec2(40, 160), 10},
		{"If you hit the enemies with your weapon you will get ", glm::ivec2(40, 180), 10},
		{"bonus score!", glm::ivec2(40, 200), 10},
		{ "<", glm::ivec2(50, SCREEN_HEIGHT - 50), 64 },
	};

	texts[HOW_TO_PLAY_SORROUNDING] =
	{
		{"SORROUNDINGS", glm::ivec2(SCREEN_WIDTH / 2 - 96, 50), 16},
		{"There are also breakable blocks and ladders!", glm::ivec2(40, 140), 10},
		{"When your weapon hits a breakable block, it breaks!", glm::ivec2(40, 160), 10},
		{"Breaking blocks also increases your score!", glm::ivec2(40, 160), 10},
		{"Ladders are climbable with the arrows up and down!", glm::ivec2(40, 200), 10},
		{"You can even shoot while you are climbing!", glm::ivec2(40, 220), 10},  
		{">", glm::ivec2(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50), 64}
	};

	texts[CREDITS] =
	{
		{"DEVELOPED BY", glm::ivec2(SCREEN_WIDTH / 2 - 96, 55), 16},
		{"Alex Herrero", glm::ivec2(SCREEN_WIDTH / 2 - 96, 80), 16},
		{"Lluc Clavera", glm::ivec2(SCREEN_WIDTH / 2 - 96, 105), 16},
		{"ORIGINAL BY", glm::ivec2(SCREEN_WIDTH / 2 - 88, 180), 16},
		{"Mitchell Corporation", glm::ivec2(SCREEN_WIDTH / 2 - 160, 205), 16},
		{"ART & MUSIC FROM", glm::ivec2(SCREEN_WIDTH / 2 - 128, 255), 16},
		{"Pang/Buster Bros", glm::ivec2(SCREEN_WIDTH / 2 - 128, 280), 16},
		{"freesound.org", glm::ivec2(SCREEN_WIDTH / 2 -104, 305), 16},
		{"SPECIAL THANKS", glm::ivec2(SCREEN_WIDTH / 2 - 112, 355), 16},
		{"Adria Lozano", glm::ivec2(SCREEN_WIDTH / 2 - 96, 380), 16},
		{"Oscar Argudo", glm::ivec2(SCREEN_WIDTH / 2 - 96, 405), 16},
		{"Bob (the dog in the picture)", glm::ivec2(SCREEN_WIDTH / 2 - 224, 430), 16},
	};

	texts[END] = {
		{"THE END", glm::ivec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1), 16},
	};

	bgMenuSheet.loadFromFile("images/Pang.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bgCreditsSheet.loadFromFile("images/Bob.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bgHowToPlaySheet.loadFromFile("images/SagradaFamiliaNight.png", TEXTURE_PIXEL_FORMAT_RGBA);
	SoundManager::instance().changeBgMusic("sounds/Main.mp3", true, false);

	engine = SoundManager::instance().getSoundEngine();
	if (menuNavSrc == nullptr) menuNavSrc = engine->addSoundSourceFromFile("sounds/menu-nav.mp3");
	//menuNavSrc->setDefaultVolume(0.5);
}

void Menu::update(int deltaTime)
{
	if (scene == MAIN_MENU) {
		if (Game::instance().getKeyUp(GLFW_KEY_UP)) {
			if (--selected < 0) selected = 3;
			engine->play2D(menuNavSrc);
		}
		else if (Game::instance().getKeyUp(GLFW_KEY_DOWN)) {
			selected = (selected + 1) % 4;
			engine->play2D(menuNavSrc);
		}
		
		if (Game::instance().getKeyUp('\r') || Game::instance().getKeyUp(GLFW_KEY_SPACE) || Game::instance().getKeyUp(GLFW_KEY_ENTER)) {
			switch (selected)
			{
			case 0:
				Game::instance().setLevel(1);
				break;
			case 1:
				scene = HOW_TO_PLAY_OBJECTIVE;
				SoundManager::instance().changeBgMusic("sounds/tutorial.mp3",true,false);
				break;
			case 2:
				scene = CREDITS;
				SoundManager::instance().changeBgMusic("sounds/8_bit_ballroom_dance.mp3",true, false);
				break;
			default:
				exit(0);
				break;
			}
		}
	}
	else {
		changeHowToPlay();
	}
}

void Menu::render()
{
	glm::mat4 modelview;
	program.use();
	program.setUniformMatrix4f("projection", projection);
	program.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	program.setUniformMatrix4f("modelview", modelview);
	program.setUniform2f("texCoordDispl", 0.f, 0.f);


	glEnable(GL_TEXTURE_2D);
	if (scene == MAIN_MENU) {
		bgMenuSheet.use();
	}

	else if (scene == CREDITS) {
		bgCreditsSheet.use();
	}

	else {
		bgHowToPlaySheet.use();
	}

	glBindVertexArray(bVao);
	glEnableVertexAttribArray(backPosLocation);
	glEnableVertexAttribArray(backTexCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);


	/*for (int i = 0; i < images[scene].size(); ++i)
	{
		if (i == 0) images[scene][i]->render(glm::vec4(0.5f));
		else images[scene][i]->render();
	}*/

	for (int i = 0; i < texts[scene].size(); ++i)
	{
		glm::vec4 color(1.f);
		if (i == selected && scene == MAIN_MENU) {
			color = glm::vec4(0.7f, 0.8f, 0.2f, 1.f);
		}

		textObj.render(texts[scene][i].text, texts[scene][i].pos + 1, texts[scene][i].textSize, glm::vec4(0, 0, 0, 1) * 0.8f);
		textObj.render(texts[scene][i].text, texts[scene][i].pos, texts[scene][i].textSize, color);
	}
	//textObj.render("Hola", glm::vec2(100, 100), 32, glm::vec4(1,1,1,1));
}
	
void Menu::theEnd()
{
		scene = END;
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if (!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();

	vector<float> backgroundVertices;
	//First triangle
	backgroundVertices.push_back(0.f); backgroundVertices.push_back(0.f);
	backgroundVertices.push_back(0.f); backgroundVertices.push_back(0.f);
	backgroundVertices.push_back(backgroundSize.x); backgroundVertices.push_back(0.f);
	backgroundVertices.push_back(1.f); backgroundVertices.push_back(0.f);
	backgroundVertices.push_back(backgroundSize.x); backgroundVertices.push_back(backgroundSize.y);
	backgroundVertices.push_back(1.f); backgroundVertices.push_back(1.f);
	//Second triangle
	backgroundVertices.push_back(0.f); backgroundVertices.push_back(0.f);
	backgroundVertices.push_back(0.f); backgroundVertices.push_back(0.f);
	backgroundVertices.push_back(backgroundSize.x); backgroundVertices.push_back(backgroundSize.y);
	backgroundVertices.push_back(1.f); backgroundVertices.push_back(1.f);
	backgroundVertices.push_back(0.f); backgroundVertices.push_back(backgroundSize.y);
	backgroundVertices.push_back(0.f); backgroundVertices.push_back(1.f);

	glGenVertexArrays(1, &bVao);
	glBindVertexArray(bVao);
	glGenBuffers(1, &bVbo);
	glBindBuffer(GL_ARRAY_BUFFER, bVbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &backgroundVertices[0], GL_STATIC_DRAW);
	backPosLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	backTexCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Menu::changeHowToPlay()
{
	switch (scene)
	{
	case HOW_TO_PLAY_OBJECTIVE:
		if (Game::instance().getKeyUp(GLFW_KEY_RIGHT)) scene = HOW_TO_PLAY_SORROUNDING;
		break;
	case HOW_TO_PLAY_POWER_UPS:
		if (Game::instance().getKeyUp(GLFW_KEY_RIGHT)) scene = HOW_TO_PLAY_ENEMIES;
		else if (Game::instance().getKeyUp(GLFW_KEY_LEFT)) scene = HOW_TO_PLAY_SORROUNDING;
		break;
	case HOW_TO_PLAY_ENEMIES:
		if (Game::instance().getKeyUp(GLFW_KEY_LEFT)) scene = HOW_TO_PLAY_POWER_UPS;
		break;
	case HOW_TO_PLAY_SORROUNDING:
		if (Game::instance().getKeyUp(GLFW_KEY_RIGHT)) scene = HOW_TO_PLAY_POWER_UPS;
		else if (Game::instance().getKeyUp(GLFW_KEY_LEFT)) scene = HOW_TO_PLAY_OBJECTIVE;
		break;
	default:
		
		break;
	}
}
