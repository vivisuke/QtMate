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
	int		m_lastX = -1;		//	直前着手位置
	int		m_lastY = -1;		//	直前着手位置
public:
	void	init() {
		m_next = BLACK;
		m_lastX = m_lastY = -1;
	}
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
	Color	get_colorGB(int x, int y) const { return m_globalBoard[y*BOARD_WD + x]; }
	bool	isValidLB(int x, int y) const { return m_isValidLB[y*BOARD_WD + x]; }
	bool	isThree(int x, int y, Color col) const;		//	三目並んだか？
	void	set_color(int x, int y, Color col) { m_localBoard[y*BOARD9_WD + x] = col; }
	void	set_colorGB(int x, int y, Color col) { m_globalBoard[y*BOARD_WD + x] = col; }
	void	updateIsValidLB(int x, int y);
private:
	Color	m_localBoard[BOARD9_SIZE];
	Color	m_globalBoard[BOARD_SIZE];
	bool	m_isValidLB[BOARD_SIZE];		//	各ローカルボードに着手可能か？
};

