#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;



TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	background.use();
	glBindVertexArray(bVao);
	glEnableVertexAttribArray(backPosLocation);
	glEnableVertexAttribArray(backTexCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < nBBlocks; ++i) {
		breakableBlocks[i].render();
	}
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile, backgroundFile;
	stringstream sstream;
	int tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> backgroundFile;
	background.loadFromFile(backgroundFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	

	backgroundSize.x = mapSize.x * blockSize;
	backgroundSize.y = mapSize.y * blockSize;

	map = new int[mapSize.x * mapSize.y];
	tileType = new TileType[mapSize.x * mapSize.y];

	getline(fin, line);
	sstream.str(line);
	sstream >> nBBlocks;
	breakableBlocks = new BreakableBlock[nBBlocks];
	for (int i = 0; i < nBBlocks; ++i) {
		int x, y, size, color;
		bool horizontal;
		getline(fin, line);
		sstream.str(line);
		sstream >> x >> y >> horizontal >> size >> color;
		glm::ivec2 inPos(x, y);
		breakableBlocks[i].init(inPos, horizontal, size, color);
		if (horizontal) {
			size = (size - 1) % 4 + 1;
			for (int j = 0; j < size; ++j) {
				tileType[y * mapSize.x + x + j] = Breakable;
			}
		}
		else {
			size = (size - 1) % 4 + 1;
			for (int j = 0; j < size; ++j) {
				tileType[(y + j)*mapSize.x + x] = Breakable;
			}
		}
		
		tileType[y * mapSize.x + x] = Breakable;
	}
	for(int j=0; j<mapSize.y; j++)
	{
		getline(fin, line);
		sstream.str(line);
		for(int i=0; i<mapSize.x; i++)
		{
			sstream >> tile;
			map[j*mapSize.x+i] = tile;
			if (tile == 0) tileType[j * mapSize.x + i] = TileMap::Air;
			else if (tile > 0 && tile <= 12) tileType[j * mapSize.x + i] = TileMap::Ladder;
			else if (tileType[j * mapSize.x + i] != TileMap::Breakable) tileType[j * mapSize.x + i] = TileMap::SolidBlock;
		}
	}

	getline(fin, line);
	sstream.str(line);
	sstream >> nBub;

	bubData = new int[nBub*4];
	for (int i = 0; i < nBub; ++i) {
		getline(fin, line);
		sstream.str(line);
		sstream >> bubData[i] >> bubData[i + 1] >> bubData[i + 2] >> bubData[i + 3];
	}

	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0 && tileType[j * mapSize.x + i] != TileMap::Breakable)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x) / tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}
	for (int i = 0; i < nBBlocks; ++i) {
		breakableBlocks[i].prepareArrays(program);
	}


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));


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

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

TileMap::TileType TileMap::getTileType(const glm::ivec2 &pos)
{
	int xTile, yTile;
	xTile = pos.x / tileSize;
	yTile = pos.y / tileSize;
	return tileType[yTile*mapSize.x + xTile];
}

bool TileMap::hookColision(const glm::ivec2 &pos, const glm::ivec2 &size)
{
	return false;
}

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(tileType[y*mapSize.x+x - 1] == TileMap::SolidBlock || tileType[y * mapSize.x + x - 1] == TileMap::Breakable)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if (tileType[y * mapSize.x + x + 1] == TileMap::SolidBlock || tileType[y * mapSize.x + x + 1] == TileMap::Breakable)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if (tileType[y * mapSize.x + x] == TileMap::SolidBlock || tileType[y * mapSize.x + x] == TileMap::Breakable)
		{
			if(*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		//cout << x << " " << y << endl;
		if (tileType[y*mapSize.x + x] == TileMap::SolidBlock || tileType[y * mapSize.x + x] == TileMap::Breakable)
		{
	
			*posY = tileSize * y + size.y;
			return true;

		}
	}

	return false;
}

int* TileMap::getBubData()
{
	return bubData;
}

int TileMap::getBubNumber() {
	return nBub;
}




























