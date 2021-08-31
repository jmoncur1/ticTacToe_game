#pragma once

#include <iostream>
#include <charconv>


struct IntRowCol {
	int row, column;
} typedef IntRowCol;

class Board
{
private:
	char board[3][3];
	char init_flag = false;
	char empty_square = ' ';
public:
	bool setSquare(char player_type, int row, int column)
	{
		if (row - 1 <= 2 && row - 1 >= 0 && column - 1 <= 2 && column - 1 >= 0)
		{
			if (board[row-1][column-1] == empty_square)
			{
				board[row-1][column-1] = player_type;
				return true;
			}
			else
			{
				std::cout << "Square already taken!" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Please enter a valid row and column, within 1 to 3." << std::endl;
			return false;
		}
	}

	void setInitFlag(bool input_init_flag) { init_flag = input_init_flag; }

	char getEmptySquareChar() { return empty_square; }
	bool getInitFlag() { return init_flag; }
	char getSquare(int row, int column)
	{
		if (row - 1 <= 2 && row - 1 >= 0 && column - 1 <= 2 && column - 1 >= 0)
		{
			return board[row - 1][column - 1];
		}
		else
		{
			throw "Tried to access square out side of board's array."; 
		}
	}

	void printBoard()
	{
		std::cout << "\n  __________________" << std::endl;
		for (int i = 0; i <= 2; i++)
		{
			std::cout << " |     |     |     |" << std::endl;
			std::cout << " |  ";
			for (int j = 0; j <= 2; j++)
			{
				std::cout << board[i][j] << "  |  ";
			}
			std::cout << std::endl;
			std::cout << " __________________" << std::endl;
		}
		std::cout<<std::endl;
	}
	void printBoardSquare(int row, int column)
	{
		if (row - 1 <= 2 && row - 1 >= 0 && column - 1 <= 2 && column - 1 >= 0)
		{
			std::cout << board[row - 1][column - 1] << std::endl;
		}
		else
		{
			std::cout << "Invalid selected square" << std::endl;
		}
	}

	void resetBoard()
	{
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				board[i][j] = empty_square;  // populate the board with the character used to signify an empty square 
			}
		}
	}

	Board()
	{
		resetBoard();
		init_flag = true;
	}

	// gameplay functions

	IntRowCol take_turn(char playerXor0, std::string player_name)
	/* Lets one player take their turn by placing thier type (X/O) on an empty square on the board */
	{
		int row, column;
		IntRowCol acceptedSquare;
		bool square_set_success = false;
		bool caused_win_flag = false; // player taking their turn resulted in a win flag
		if (getInitFlag() == true)
		{
			std::cout << "\nIt is " << player_name << "'s turn:" << std::endl;
			printBoard();
			while (square_set_success == false)
			{
				std::cout << "Enter row :";
				std::cin >> row;
				std::cout << "Enter colum :";
				std::cin >> column;
				square_set_success = setSquare(playerXor0, row, column);
			}
			acceptedSquare.row = row;
			acceptedSquare.column = column;
			return acceptedSquare;
		}
		else
		{
			throw "Attempt for player to take turn before board has been initaliazed.";
		}	
	}

	bool take9AlternatingTurns(Player &player_1, Player &player_2, int game_no)
	{
		bool player1_win_flag = false;
		bool player2_win_flag = false;
		IntRowCol chosenSquare;
		resetBoard();  // clear the board from any previous games
		std::cout << "\n************\nThis is game number " << game_no << std::endl;
		if (game_no % 2 == 0)
		{
			for (int i = 0; i <= 7; i = i + 2) // allow 8 turns to be taken
			{
				chosenSquare = take_turn(player_1.getPlayerType(), player_1.getName());
				if ( testForWin(chosenSquare.row, chosenSquare.column, player_1.getPlayerType()) == true)
				{
					player_1.increment_score();
					printWinner(player_1.getName());
					return true;
				}
				chosenSquare =  take_turn(player_2.getPlayerType(), player_2.getName());
				if (testForWin(chosenSquare.row, chosenSquare.column, player_2.getPlayerType()) == true)
				{
					player_2.increment_score();
					printWinner(player_1.getName());
					return true;
				}
			}
			chosenSquare =  take_turn(player_1.getPlayerType(), player_1.getName()); // final turn to fill board
			if (testForWin(chosenSquare.row, chosenSquare.column, player_1.getPlayerType()) == true)
			{
				player_1.increment_score();
				printWinner(player_1.getName());
				return true;
			}
			std::cout << "\nIt's a draw!\n" << std::endl;
			player_1.increment_score();
			player_1.printVerboseScore();
			return true;
		}
		else
		{
			for (int i = 0; i <= 7; i = i + 2)
			{
				chosenSquare = take_turn(player_2.getPlayerType(), player_2.getName());
				if (testForWin(chosenSquare.row, chosenSquare.column, player_2.getPlayerType()) == true)
				{
					player_2.increment_score();
					printWinner(player_2.getName());
					return true;
				}
				chosenSquare = take_turn(player_1.getPlayerType(), player_1.getName());
				if (testForWin(chosenSquare.row, chosenSquare.column, player_1.getPlayerType()) == true)
				{
					player_1.increment_score();
					printWinner(player_1.getName());
					return true;
				}
			}
			chosenSquare = take_turn(player_2.getPlayerType(), player_2.getName());
			if (testForWin(chosenSquare.row, chosenSquare.column, player_2.getPlayerType()) == true)
			{
				player_2.increment_score();
				printWinner(player_2.getName());
				return true;
			}
			printBoard();
			std::cout << "\nIt's a draw!\n" << std::endl;
			player_1.printVerboseScore();
			return true;
		}
	}

	bool testForWin(int row_placement, int column_placement, char playerType)
	/* Function tests new turn taken by a player to see if it results in a win */
	{
		bool consectutiveCharsFlag = false;
		char hori_1, hori_2, hori_3;
		char vert_1, vert_2, vert_3;
		char lr_dia_1, lr_dia_2, lr_dia_3; // diagonal going top left to bottom right
		char rl_dia_1, rl_dia_2, rl_dia_3; // diagonal going top right to bottom left
		// horizontal search
		hori_1 = getSquare(row_placement, 1);
		hori_2 = getSquare(row_placement, 2);
		hori_3 = getSquare(row_placement, 3);
		if (hori_1 == hori_2 && hori_2 == hori_3)
		{
			consectutiveCharsFlag = true;
			return consectutiveCharsFlag;
		}
		// vertical search
		vert_1 = getSquare(1, column_placement);
		vert_2 = getSquare(2, column_placement);
		vert_3 = getSquare(3, column_placement);
		if (vert_1 == vert_2 && vert_2 == vert_3)
		{
			consectutiveCharsFlag = true;
			return consectutiveCharsFlag;
		}
		// tl-br search
		lr_dia_1 = getSquare(1, 1);
		lr_dia_2 = getSquare(2, 2);
		lr_dia_3 = getSquare(3, 3);
		if (lr_dia_1 == lr_dia_2 && lr_dia_2 == lr_dia_3 && lr_dia_1 != getEmptySquareChar())
		{
			consectutiveCharsFlag = true;
			return consectutiveCharsFlag;
		}
		// tl-br search
		rl_dia_1 = getSquare(1, 3);
		rl_dia_2 = getSquare(2, 2);
		rl_dia_3 = getSquare(3, 1);
		if (rl_dia_1 == rl_dia_2 && rl_dia_2 == rl_dia_3 && rl_dia_1 != getEmptySquareChar())
		{
			consectutiveCharsFlag = true;
			return consectutiveCharsFlag;
		}
	}

	void printWinner(std::string winners_name)
	{
		std::cout << winners_name << " won this game, congradulations!" << std::endl;
	}
};

