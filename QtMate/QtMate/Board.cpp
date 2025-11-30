#include "Board.h"

void Board::init() {
	for(auto& v: m_localBoard) v = EMPTY;
	for(auto& v: m_globalBoard) v = EMPTY;
	for(auto& v: m_isValidLB) v = true;
}
void Board::updateIsValidLB(int x, int y) {
	int ix = (y%BOARD_WD)*BOARD_WD + (x%BOARD_WD);
	for(auto& v: m_isValidLB) v = false;
	m_isValidLB[ix] = true;
}
