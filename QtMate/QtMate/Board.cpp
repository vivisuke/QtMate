#include "Board.h"

void Board::init() {
	for(auto& v: m_localBoard) v = EMPTY;
	for(auto& v: m_globalBoard) v = EMPTY;
}
