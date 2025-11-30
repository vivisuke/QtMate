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

struct Global {
	Color	m_next = BLACK;		//	次の手番
};

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
	Color	get_color(int x, int y) const { return m_localBoard[y*BOARD9_WD + x]; }
	void	set_color(int x, int y, Color col) { m_localBoard[y*BOARD9_WD + x] = col; }
private:
	Color	m_localBoard[BOARD9_SIZE];
	Color	m_globalBoard[BOARD_SIZE];
};

