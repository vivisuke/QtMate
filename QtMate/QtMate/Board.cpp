#include "Board.h"

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
