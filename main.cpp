/*
Entry point and flow of tic tac toe game
*/

#include <iostream>
#include "player_class.h"
#include "game_board.h"

int main(){
	Board the_game;
	int deathmatch_counter = 0; // count no sudden death games in case of a draw
	
	std::cout << "\nWelcome to Tic Tac Toe!" << std::endl;
	Player player_1;
	Player player_2;

	player_2.deconflictPlayerTypes(player_1);

	for (int i = 0; i <= 2; i++)
	{
		the_game.take9AlternatingTurns(player_1, player_2, i+1);
	}
	player_1.printVerboseScore();
	player_2.printVerboseScore();
	// is there a winner?
	if (player_1.getScore() > player_2.getScore())
	{
		std::cout << "Congradulations " << player_1.getName() << ", you won " << player_1.getScore() << " of 3 games!" << std::endl;
	}
	else if (player_2.getScore() > player_1.getScore())
	{
		std::cout << "Congradulations " << player_1.getName() << ", you won " << player_1.getScore() << " of 3 games!" << std::endl;
	}
	else if (player_1.getScore() == player_2.getScore())
	{
		std::cout << "Its a draw :0" << std::endl;
		while (player_1.getScore() == player_2.getScore())
		{
			deathmatch_counter = deathmatch_counter + 1;
			the_game.take9AlternatingTurns(player_1, player_2, deathmatch_counter);
		}
		if (player_1.getScore() > player_2.getScore())
		{
			std::cout << "Congradulations " << player_1.getName() << ", you won through sudden death!" << std::endl;
		}
		else if (player_2.getScore() > player_1.getScore())
		{
			std::cout << "Congradulations " << player_1.getName() << ", you won though sudden death!" << std::endl;
		}
	}

}
