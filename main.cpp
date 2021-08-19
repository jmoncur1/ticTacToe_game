/*
Entry point and flow of tic tac toe game
*/

#include <iostream>
#include "player_class.h"

int main(){
	for(int i = 0; i <= 2; i++) {
		std::cout<<i<<"\n";
	}
	std::cout << "\nWelcome to Tic Tac Toe!" << std::endl;
	Player player_1;
	Player player_2;
	int winner;
	for (int i = 0; i <= 2; i++) {
		std::cout << "Who won[1, 2]: " << std::endl;
		std::cin >> winner;
		if (winner==1)
		{
			player_1.increment_score();
			std::cout << "Aggghhh" << std::endl;
		}
		else if (winner == 2)
		{
			player_2.increment_score();
			std::cout << "Eeeeeagghh" << std::endl;
		}
	}

	std::cout << "\nPlayer 1 score = " << player_1.getScore() << "\nPlayer 2 score = " << player_2.getScore() << std::endl;

	// is there a winner?
	if (player_1.getScore() > player_2.getScore())
	{
		std::cout << "Congradulations Player 1, you won " << player_1.getScore() << " of 3 games!" << std::endl;
	}
	else if (player_2.getScore() > player_1.getScore() )
	{
		std::cout << "Congradulations Player 2, you won " << player_2.getScore() << " of 3 games!" << std::endl;
	}
	else if (player_1.getScore() == player_2.getScore() )
	{
		std::cout << "Its a draw :0" << std::endl;
	}
}