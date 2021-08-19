#pragma once

#include <iostream>
#include <string>
#include <string>

enum PlayerType
{
	NAUGHTS = 0, CROSSES = 1
};

class Player
{
private:
	int score;
	std::string name;
	PlayerType the_player_type;
	bool init_flag=false;
	
public:
	//setter functions
	void setScore(int input_score ) { score = input_score; }
	void setName(std::string input_name) { name = input_name; }
	void setPlayerType(PlayerType input_player_type) { the_player_type = input_player_type; }
	void setInitFlag(bool input_init_flag) { init_flag = input_init_flag; }
	// print functions
	void printScore() { std::cout << score << std::endl; }
	void printName() { std::cout << name << std::endl; }
	void printPlayerType() { std::cout << the_player_type << std::endl; }
	void printInitFlag() { std::cout << init_flag << std::endl; }
	// getter functions
	int getScore() { return score; }
	std::string getName() { return name; }
	PlayerType getPlayerType() { return the_player_type; }
	bool getInitFlag() { return init_flag; }

	// increment score after a winning a game
	int increment_score()
	{
		setScore(getScore() + 1);
		return 0;
	}

	Player() //init function
	{
		std::string input_name;
		int user_input;
		PlayerType input_type;
		std::cout << "Enter name: ";
		std::cin >> input_name;
		std::cout << "Enter player type [0 for naughts, 1 for crosses]: ";
		std::cin >> user_input;
		
		input_type = static_cast<PlayerType>(user_input);

		setName(input_name);
		setPlayerType(input_type);
		setScore(0);
		setInitFlag(true);
	}
	~Player() {}; // deconstructor
};