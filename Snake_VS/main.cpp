#include "Segment.h"
#include "GameLogic.h"


bool sortcol(const std::vector <std::string> & v1,
	const std::vector<std::string> & v2) {
	return std::stoi(v1[2]) > std::stoi(v2[2]);
}

int main() {
	
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Window");
	window.setFramerateLimit(61);

	
	sf::Clock clock;
	float timer = 0;
	float delay = 0.1;
	
	sf::Text gameTitle, playerName, instruction, text;
	sf::Font font;
	font.loadFromFile("GreatVibes-Regular.otf");
	gameTitle.setFont(font);
	gameTitle.setString("SNAKE GAME");
	gameTitle.setCharacterSize(80);
	gameTitle.setFillColor(sf::Color::Red);
	gameTitle.setStyle(sf::Text::Bold);
	gameTitle.setPosition(sf::Vector2f(50, 50));
	instruction.setFont(font);
	instruction.setString("Type name and hit enter!");
	instruction.setCharacterSize(60);
	instruction.setFillColor(sf::Color::Blue);
	instruction.setStyle(sf::Text::Bold);
	instruction.setPosition(sf::Vector2f(50, 200));
	playerName.setFont(font);
	playerName.setCharacterSize(50);
	playerName.setFillColor(sf::Color::Black);
	playerName.setPosition(sf::Vector2f(50, 300));
	text.setFont(font);
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(50, 50));
	//main loop
	while (window.isOpen()) {
		std::string player_name = "";
		GameLogic gl;
		sf::Event event;
		//first window loop
		bool notStartGame = true;
		
		playerName.setPosition(sf::Vector2f(50, 300));
		while (notStartGame) {
			window.clear(sf::Color::White);
			window.draw(gameTitle);
			window.draw(instruction);
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
					return 0;
				}
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128 && event.text.unicode > 48){
						std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
						player_name = player_name + static_cast<char>(event.text.unicode);
						std::cout << "player name: " << player_name << std::endl;
					}
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::BackSpace) {
						if(player_name.length() > 0){
							player_name.pop_back();
							std::cout << "player name: " << player_name << std::endl;
						}
					}
					if (event.key.code == sf::Keyboard::Enter) {
						// save name and break this loop to start game
						playerName.setString("");
						notStartGame = false;
					}
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
						return 0;
					}
				}
			}
			playerName.setString(player_name);
			window.draw(playerName);
			window.display();

		}
		time_t begin = time(NULL);
		gl.setGameLost(false);
		//game loop
		while (gl.getGameLost() == false) {
			float time_inGame = clock.restart().asSeconds();
			timer = timer + time_inGame;
			
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
					return 0;
				}
				//Left & Right controll
				if (event.type == sf::Event::KeyReleased) {

					if (event.key.code == sf::Keyboard::Left) {
						gl.Left();
					}
					else if (event.key.code == sf::Keyboard::Right) {
						gl.Right();
					}
					
				}
			}

			if (timer > delay) {
				timer = 0;
				gl.doAllCheckers();
			}

			gl.update();

			window.clear(sf::Color::White);

			// drawing plain with elements
			for (int i = 0; i < vertical; i++)
			{
				for (int j = 0; j < horizontal; j++)
				{
					window.draw(gl.plain[j][i].getSegment_unit());
				}
			}

			window.display();
		}
		time_t end = time(NULL);


		double time_of_play = difftime(end, begin);
		int score = gl.getSnakeLen() - 1;

		bool backToFirstView = false;
		playerName.setPosition(sf::Vector2f(50, 200));
		//save score, display, score board and restart loop

		std::fstream my_f;
		std::string temp;
		std::vector<std::string> data_from_f;
		std::vector<std::string> temp_vector;
		std::vector<std::vector<std::string>> data_from_f2;
		my_f.open("wyniki.txt", std::ios::app);
		my_f.close();

		my_f.open("wyniki.txt", std::ios::in);
		if (my_f.is_open()) {
			std::cout << "plik otwarty2";
		}
		int i = 0;
		while (std::getline(my_f, temp)) {
			data_from_f.push_back(temp);
		}
		my_f.close();
		data_from_f.push_back(player_name + " score: " + std::to_string(score) + "\n");
		if (data_from_f.empty() == false) {
			for (int i = 0; i < data_from_f.size(); i++) {
				std::istringstream iss(data_from_f[i]);
				std::string temp_test;
				data_from_f2.push_back(temp_vector);
				while (iss >> temp_test) {
					data_from_f2[i].push_back(temp_test);
				}
			}
		}


		//sort rows by score
		sort(data_from_f2.begin(), data_from_f2.end(), sortcol);

		//delete the worst if more than 10
		if (data_from_f2.size() > 10) {
			data_from_f2.pop_back();
		}

		//accumulate into string sentence
		data_from_f.clear();
		for (int i = 0; i < data_from_f2.size(); i++) {
			std::string helpfull_temporary = "";
			for (int j = 0; j < data_from_f2[i].size(); j++) {
				helpfull_temporary = helpfull_temporary + data_from_f2[i][j] + " ";
			}
			data_from_f.push_back(helpfull_temporary+"\n");
		}
		//clearing a file
		my_f.open("wyniki.txt", std::ofstream::out | std::ofstream::trunc);

		my_f.close();

		//write 10 best scores 
		my_f.open("wyniki.txt", std::ios::app);
		if (my_f.is_open()) {
			std::cout << "plik otwarty3" << std::endl;
		}
		for (int i = 0; i < data_from_f.size(); i++) {
			my_f << data_from_f[i];
		}
		my_f.close();
		

		while (backToFirstView == false) {
			


			window.clear(sf::Color::White);
			text.setString("Game over");
			window.draw(text);
			for (int i = 0; i < data_from_f.size(); i++) {
				playerName.setString(std::to_string(i+1)+ ". " + data_from_f[i]);
				playerName.setPosition(50, 200 + i * 35);
				window.draw(playerName);
			}
			
			

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
					return 0;
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Enter) {
						backToFirstView = true;
					}
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
						return 0;
					}
					
				}

			}
			
			window.display();
		}

	}
	return 0;
}


