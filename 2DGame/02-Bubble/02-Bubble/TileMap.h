#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	enum TileType {
		Ladder,
		Air,
		SolidBlock,
		BreakableBlock
	};
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }
	TileType getTileType(glm::ivec2 pos);

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	int* getBubData();
	int getBubNumber();

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao,bVao;
	GLuint vbo,bVbo;
	GLint posLocation, texCoordLocation;
	GLint backPosLocation, backTexCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize, backgroundSize;
	int tileSize, blockSize;
	Texture tilesheet, background;
	glm::vec2 tileTexSize;
	int *map;
	TileType *tileType;
	int nBub;
	int* bubData;
};


#endif // _TILE_MAP_INCLUDE


