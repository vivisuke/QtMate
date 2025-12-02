#include <vector>
#include <random>
#include "Board.h"

using namespace std;

static std::random_device rd;
static std::mt19937 rgen(rd()); 
//static std::mt19937 rgen(0); 
//std::mt19937_64 rgen64(rd());		// 64ビット版

#define		is_empty()	empty()

void Board::init() {
	for(auto& v: m_localBoard) v = EMPTY;
	for(auto& v: m_globalBoard) v = EMPTY;
	for(auto& v: m_isValidLB) v = true;
}
void Board::updateIsValidLB(int x, int y) {
	int ix = (y%BOARD_WD)*BOARD_WD + (x%BOARD_WD);
	if( m_globalBoard[ix] == EMPTY ) {
		for(auto& v: m_isValidLB) v = false;
		m_isValidLB[ix] = true;
	} else {
		for(auto& v: m_isValidLB) v = true;
	}
}
bool Board::isThree(int x, int y, Color col) const {
	int x0 = x - x % 3;		//	ローカルボード内最左位置
	int y0 = y - y % 3;		//	ローカルボード内最上位置
	if( get_color(x0, y) == col && get_color(x0+1, y) == col && get_color(x0+2, y) == col )
		return true;
	if( get_color(x, y0) == col && get_color(x, y0+1) == col && get_color(x, y0+2) == col )
		return true;
	if( get_color(x0, y0) == col && get_color(x0+1, y0+1) == col && get_color(x0+2, y0+2) == col )
		return true;
	if( get_color(x0, y0+2) == col && get_color(x0+1, y0+1) == col && get_color(x0+2, y0) == col )
		return true;
	return false;
}
int Board::sel_moveRandom() const {
	vector<int> lst;
	for(int y = 0; y < BOARD9_WD; ++y) {
		for(int x = 0; x < BOARD9_WD; ++x) {
			if( m_isValidLB[(y/3)*BOARD_WD + (x/3)] && get_color(x, y) == EMPTY ) {
				lst.push_back(y * BOARD9_WD + x);
			}
		}
	}
	if( lst.is_empty() ) return -1;
	return lst[rgen() % lst.size()];
}
