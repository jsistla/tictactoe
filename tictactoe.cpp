// tictactoe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class board {
public:
	std::vector<char> positions = std::vector<char>(9);
	char active_player;
	// handles the printing of the board
	board() {
		string mystr;
		cout << "Let's play tic-tac-toe. Who will start? X or O? ";
		getline(cin, mystr);
		stringstream(mystr) >> active_player;
		while (active_player != 'X' && active_player != 'O') {
			cout << "Try again! Enter either X or O ";
			getline(cin, mystr);
			stringstream(mystr) >> active_player;
		}
	}
	void display_board() {
		cout << " _ _ _   \n";
		cout << "|" << positions[0] << "|" << positions[1] << "|" << positions[2] << "|\n";
		cout << "|" << positions[3] << "|" << positions[4] << "|" << positions[5] << "|\n";
		cout << "|" << positions[6] << "|" << positions[7] << "|" << positions[8] << "|\n\n\n";
	}
	// updates the position tracker
	void update_position(char player, int pos) {
		positions[pos] = player;
	}
};

int ask_for_input(board * myboard) {
	unsigned int position;
	string mystr;
	cout << "It's your turn " << myboard->active_player << ". Enter a position to play  ";
	getline(cin, mystr);
	stringstream(mystr) >> position;

	while (position > 9 || position < 1 || myboard->positions[position-1] != '\0') {
		cout << "Not a valid position, enter a number from 1-9 inclusive ";
		getline(cin, mystr);
		stringstream(mystr) >> position;
	}
	return position-1;
}

bool check_for_winner(board * myboard) {
	bool winner = false;
	auto positions = myboard->positions;
	// row 0
	if (positions[0] == positions[1] && positions[1] == positions[2]) {
		if (positions[0] == 'X' || positions[0] == 'O')
			winner = true;
	}	
	// row 1
	else if (positions[3] == positions[4] && positions[4] == positions[5]) {
		if (positions[3] == 'X' || positions[3] == 'O')
			winner = true;
	}
	// row 2
	else if (positions[6] == positions[7] && positions[7] == positions[8]) {
		if (positions[6] == 'X' || positions[6] == 'O')
			winner = true;
	}
	// topleft-bottomright diagonal
	else if (positions[0] == positions[4] && positions[4] == positions[8]) {
		if (positions[0] == 'X' || positions[0] == 'O')
			winner = true;
	}
	// bottomLeft - topRight diagonal
	else if (positions[2] == positions[4] && positions[4] == positions[6]) {
		if (positions[2] == 'X' || positions[2] == 'O')
			winner = true;
	}
	// col 0
	else if (positions[0] == positions[3] && positions[3] == positions[6]) {
		if (positions[0] == 'X' || positions[0] == 'O')
			winner = true;
	}
	// col 1
	else if (positions[1] == positions[4] && positions[4] == positions[7]) {
		if (positions[1] == 'X' || positions[1] == 'O')
			winner = true;
	}
	// col 2
	else if (positions[2] == positions[5] && positions[5] == positions[8]) {
		if (positions[2] == 'X' || positions[2] == 'O')
			winner = true;
	}
	return winner;
}

bool pos_available(board * myboard) {
	bool position_free = false;
	for (auto i = 0; i <= 8; i++) {
		if (myboard->positions[i] == '\0')
			position_free = true;
	}
	return position_free;
}


int main()
{
	board myboard;
	myboard.display_board();
	int pos;
	bool is_winner = false;
	while (!is_winner && pos_available(&myboard)){
		// play a turn
		pos = ask_for_input(&myboard);
		myboard.update_position(myboard.active_player, pos);
		myboard.display_board();

		// check for winner
		is_winner = check_for_winner(&myboard);
		if (is_winner) {
			cout << "Game Over: Player " << myboard.active_player << " has won!\n\n";
		}

		// switch player turns
		switch (myboard.active_player)
		{
		case 'X':
			myboard.active_player = 'O'; break;
		case 'O':
			myboard.active_player = 'X'; break;
		default:
			break;
		}
	}


	system("PAUSE");
}

