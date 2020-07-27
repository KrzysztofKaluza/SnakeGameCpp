#include "GameLogic.h"


GameLogic::GameLogic() {
	this->direction = 3;
	this->snake_len = 1;
	plain_segment.setUnitColor(sf::Color::Yellow);
	plain_segment.setBorderColor(sf::Color::Black);
	plain_segment.setBorderThick(1);
	plain_segment.setType(0);
	for (int i = 0; i < FULL_LEN_SNAKE; i++) {
		snake[i].setType(2);
		snake[i].setUnitColor(sf::Color::Blue);
		snake[i].setBorderColor(sf::Color::White);
		snake[i].setBorderThick(2);
		snake[i].setPosition((int)(horizontal / 2), (int)(vertical / 2));
	}
	fruit.setType(3);
	fruit.setUnitColor(sf::Color::Red);
	for (int j = 0; j < OBSTACLE_NUM; j++) {
		obstacle[j].setUnitColor(sf::Color::Color(200, 200, 200, 255));
		obstacle[j].setBorderColor(sf::Color::Red);
		obstacle[j].setBorderThick(2);
		obstacle[j].setType(1);
	}

	placeAFruit();
}

void GameLogic::setDirection(int direction) {
	this->direction = direction;
}

int GameLogic::getDirection() {
	return this->direction;
}

void GameLogic::setSnakeLen(int snake_len) {
	this->snake_len = snake_len;
}

int GameLogic::getSnakeLen() {
	return this->snake_len;
}

void GameLogic::setGameLost(bool gameLost) {
	this->gameLost = gameLost;
}

bool GameLogic::getGameLost() {
	return gameLost;
}

void GameLogic::SnakeMovement() {

	for (int i = snake_len; i > 0; i--) {
		snake[i].setPosition(snake[i - 1].getXPosition(), snake[i - 1].getYPosition());
	}
	// Down
	if (direction == 0) {
		snake[0].setPosition(snake[0].getXPosition(), snake[0].getYPosition() + 1);
	}
	// Left
	else if (direction == 1) {
		snake[0].setPosition(snake[0].getXPosition() - 1, snake[0].getYPosition());
	}
	// Up
	else if (direction == 2) {
		snake[0].setPosition(snake[0].getXPosition(), snake[0].getYPosition() - 1);
	}
	// Right
	else if (direction == 3) {
		snake[0].setPosition(snake[0].getXPosition() + 1, snake[0].getYPosition());
	}

}

void GameLogic::Left() {
	int current_direction = getDirection();
	switch (current_direction) {
	case 0:
		setDirection(3);
		break;
	case 1:
		setDirection(0);
		break;
	case 2:
		setDirection(1);
		break;
	case 3:
		setDirection(2);
		break;
	default:
		exit(EXIT_FAILURE);
	}
}

void GameLogic::Right() {
	int current_direction = getDirection();
	switch (current_direction) {
	case 0:
		setDirection(1);
		break;
	case 1:
		setDirection(2);
		break;
	case 2:
		setDirection(3);
		break;
	case 3:
		setDirection(0);
		break;
	default:
		exit(EXIT_FAILURE);
	}
}

void GameLogic::checkIfEatsItself() {
	for (int i = 1; i < snake_len; i++) {
		if (snake[0].getXPosition() == snake[i].getXPosition() && snake[0].getYPosition() == snake[i].getYPosition()) {
			this->gameLost = true;
			std::cout << "lost game" << std::endl;
		}
	}
}

void GameLogic::placeAFruit() {
	srand(time(0));
	int x_val = (rand() % (horizontal - 2)) + 1;
	srand(time(0) * 17);
	int y_val = (rand() % (vertical - 2)) + 1;
	this->fruit.setPosition(x_val, y_val);
}

void GameLogic::headPosition() {
	std::cout << "x: " << snake[0].getXPosition() << "y: " << snake[0].getYPosition() << std::endl;
}

bool GameLogic::checkIfSnakeEatsFruit() {
	if (snake[0].getXPosition() == fruit.getXPosition() && snake[0].getYPosition() == fruit.getYPosition()) {
		std::cout << "fruit has been eaten" << std::endl;
		return true;
	}
	return false;
}

void GameLogic::addSegmentToSnake() {
	this->snake_len = this->snake_len + 1;
}

void GameLogic::checkIfHitsWall() {
	for (int i = 0; i < OBSTACLE_NUM; i++) {
		if (snake[0].getXPosition() == obstacle[i].getXPosition() && snake[0].getYPosition() == obstacle[i].getYPosition()) {
			this->gameLost = true;
			std::cout << "lost game" << std::endl;
		}
	}
}

void GameLogic::update() {
	for (int i = 0; i < vertical; i++)
	{
		for (int j = 0; j < horizontal; j++)
		{
			plain_segment.setPosition(j, i);
			plain[j][i] = plain_segment;
		}
	}


	int k = 0;
	for (int i = 0; i < horizontal; i++)
	{
		obstacle[k].setPosition(i, 0);
		plain[i][0] = obstacle[k];
		k++;
	}
	for (int i = 1; i < vertical - 1; i++)
	{
		obstacle[k].setPosition(0, i);
		plain[0][i] = obstacle[k];
		k++;
		obstacle[k].setPosition(horizontal - 1, i);
		plain[horizontal - 1][i] = obstacle[k];
		k++;
	}
	for (int i = 0; i < horizontal; i++)
	{
		obstacle[k].setPosition(i, vertical - 1);
		plain[i][vertical - 1] = obstacle[k];
		k++;
	}


	for (int i = 0; i < getSnakeLen(); i++) {
		snake[i].setPosition(snake[i].getXPosition(), snake[i].getYPosition());
		plain[snake[i].getXPosition()][snake[i].getYPosition()] = snake[i];
	}

	plain[fruit.getXPosition()][fruit.getYPosition()] = fruit;
}

void GameLogic::doAllCheckers() {
	SnakeMovement();
	checkIfEatsItself();
	checkIfHitsWall();
	headPosition();
	if (checkIfSnakeEatsFruit()) {
		addSegmentToSnake();
		placeAFruit();
	}
}

void GameLogic::debug_display() {
	for (int i = 0; i < vertical; i++) {
		for (int j = 0; j < horizontal; j++) {
			std::cout << plain[j][i].getType();
		}
		std::cout << "\n";
	}
}
