#pragma once
#include <iostream>

enum {
	EMPTY = 0, BLACK, WHITE,
};

const int BOARD_WD = 3;
const int BOARD_SIZE = BOARD_WD * BOARD_WD;
const int BOARD9_WD = 9;
const int BOARD9_SIZE = BOARD9_WD * BOARD9_WD;

using Color = char;

class Board
{
public:
	Board() {
		std::cout << "Board::Board()" << std::endl;
		init();
	}
	~Board() {
		std::cout << "Board::~Board()" << std::endl;
	}
public:
	void	init();
private:
	Color	m_localBoard[BOARD9_SIZE];
	Color	m_globalBoard[BOARD_SIZE];
};

