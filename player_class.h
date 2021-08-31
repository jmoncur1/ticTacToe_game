#pragma once

#include <iostream>
#include <string>

class Player
{
private:
	int score;
	std::string name;
	char the_player_type;
	bool init_flag=false;
	
public:
	//setter functions
	void setScore(int input_score ) { score = input_score; }
	void setName(std::string input_name) { name = input_name; }
	void setPlayerType(char x_or_o) { the_player_type = x_or_o; }
	void setInitFlag(bool input_init_flag) { init_flag = input_init_flag; }
	// print functions
	void printScore() { std::cout << score << std::endl; }
	void printName() { std::cout << name << std::endl; }
	void printPlayerType() { std::cout << the_player_type << std::endl; }
	void printInitFlag() { std::cout << init_flag << std::endl; }
	void printVerboseScore() { std::cout << name << "' s score is: " << score << std::endl; }
	// getter functions
	int getScore() { return score; }
	std::string getName() { return name; }
	char getPlayerType() { return the_player_type; }
	bool getInitFlag() { return init_flag; }

	// increment score after a winning a game
	int increment_score()
	{
		setScore(getScore() + 1);
		return 0;
	}

	char inputXor0()
	{
		char user_input;
		bool success_flag = false;
		while (success_flag == false)
		{
			std::cout << "Enter player naughts or crosses [X, O]: ";
			std::cin >> user_input;
			if (user_input == 'X' || user_input == 'O')
			{
				success_flag = true;
				return user_input;
			}
			else
			{
				std::cout << "Please choose valid input.\n" << std::endl;
			}
		}
	}

	bool deconflictPlayerTypes(Player otherPlayer)
	{
		/* Checks if players have the same player type (naughts or crosses), and requests player whom the function is called from to change if they do*/
		char new_x_or_o;
		char taken_player_type = otherPlayer.getPlayerType();
		bool deconflict_success_flag = false;
		if (getPlayerType() != taken_player_type)
		{
			return true; // do nothing as players do not have same type 
		}
		else
		{
			std::cout << "Player " << otherPlayer.getName() << " has already taken " << taken_player_type << ". Please choose the other." << std::endl;
			while (deconflict_success_flag == false)
			{
				new_x_or_o = inputXor0();
				if (new_x_or_o != taken_player_type)
				{
					setPlayerType(new_x_or_o);
					deconflict_success_flag = true;
					return true;
				}
				else
				{
					std::cout << "Player " << otherPlayer.getName() << " has already taken " << taken_player_type << ". Please choose the other." << std::endl;
					deconflict_success_flag = false;
				}
			}
		}
	}

	Player() //init function
	{
		std::string input_name;
		char x_or_o;
		std::cout << "\nEnter name: ";
		std::cin >> input_name;
		x_or_o = inputXor0();

		setName(input_name);
		setPlayerType(x_or_o);
		setScore(0);
		setInitFlag(true);
	}
	~Player() {}; // deconstructor
};
