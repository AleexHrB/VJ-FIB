#pragma once
#include "Enemy.h"

class Bubble : public Enemy {
public:
	enum Color {
		RED,
		BLUE,
		GREEN
	};

	enum Size {
		BIG,
		MID,
		SMALL,
		TINY,
		NONE
	};
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Color c, Size s, const glm::vec2& initPos, const glm::vec2& speed);
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	bool checkCollision(const pair<glm::ivec2, glm::ivec2>& hitbox) override;
	void changeGravity(float g);
	unsigned int getBonus() override;
	Size getSize();
	Color getColor();
private:
	float t = 0;
	glm::vec2 initPosBubble;
	Size s;
	Color c;
	//Source: https://algo.monster/liteproblems/1401
	inline unsigned int getMinimumDistance(int minEdge, int maxEdge, int centerCoord) {
		if (centerCoord >= minEdge && centerCoord <= maxEdge) {
			// The center is inside the rectangle along this axis, so distance is 0.
			return 0;
		}
		// The center is outside the rectangle; calculate the distance to the closer edge.
		return centerCoord < minEdge ? minEdge - centerCoord : centerCoord - maxEdge;
	}

};