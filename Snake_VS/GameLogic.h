#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "Segment.h"
class GameLogic {
private:
	int direction;
	int snake_len;
	bool gameLost;
public:
	Segment fruit;
	Segment snake[FULL_LEN_SNAKE];
	Segment plain_segment;
	Segment plain[horizontal][vertical];
	Segment obstacle[OBSTACLE_NUM];
	GameLogic();
	void setDirection(int direction);
	int getDirection();
	void setSnakeLen(int snake_len);
	int getSnakeLen();
	void setGameLost(bool gameLost);
	bool getGameLost();
	void SnakeMovement();
	void Left();
	void Right();
	void checkIfEatsItself();
	void placeAFruit();
	void headPosition();
	bool checkIfSnakeEatsFruit();
	void addSegmentToSnake();
	void checkIfHitsWall();
	void update();
	void doAllCheckers();
	void debug_display();
};

#endif
