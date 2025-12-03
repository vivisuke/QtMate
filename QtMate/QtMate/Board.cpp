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
	for(auto& v: m_nEmpty) v = BOARD_SIZE;
}
void Board::updateIsValidLB(int x, int y) {				//	次に着手可能ローカルボードかどうかを判定
	int ix = (y%BOARD_WD)*BOARD_WD + (x%BOARD_WD);
	if( m_globalBoard[ix] == EMPTY && m_nEmpty[ix] != 0 ) {
		for(auto& v: m_isValidLB) v = false;
		m_isValidLB[ix] = true;
	} else {
		for(auto& v: m_isValidLB) v = true;
	}
}
bool Board::put_color(int x, int y, Color col) {
	bool won = false;
	set_color(x, y, col);
	m_nEmpty[(y/3)*3 + x/3] -= 1;
	if( isThree(x, y, col) ) {
		set_colorGB(x/3, y/3, col);
		won = isThreeGB(x/3, y/3, col);
	}
	updateIsValidLB(x, y);
	return won;
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
bool Board::isThreeGB(int gx, int gy, Color col) const {
	int x0 = gx - gx % 3;		//	ローカルボード内最左位置
	int y0 = gy - gy % 3;		//	ローカルボード内最上位置
	if( get_colorGB(x0, gy) == col && get_colorGB(x0+1, gy) == col && get_colorGB(x0+2, gy) == col )
		return true;
	if( get_colorGB(gx, y0) == col && get_colorGB(gx, y0+1) == col && get_colorGB(gx, y0+2) == col )
		return true;
	if( get_colorGB(x0, y0) == col && get_colorGB(x0+1, y0+1) == col && get_colorGB(x0+2, y0+2) == col )
		return true;
	if( get_colorGB(x0, y0+2) == col && get_colorGB(x0+1, y0+1) == col && get_colorGB(x0+2, y0) == col )
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
int evaluateLine(int c1, int c2, int c3) {
    int blackCount = 0;
    int whiteCount = 0;
    if( c1 == BLACK ) blackCount+= 1;
    else if( c1 == WHITE ) whiteCount+= 1;
    if( c2 == BLACK ) blackCount+= 1;
    else if( c2 == WHITE ) whiteCount+= 1;
    if( c3 == BLACK ) blackCount+= 1;
    else if( c3 == WHITE ) whiteCount+= 1;

    if( blackCount != 0 && whiteCount != 0 ) return 0;
	// スコア変換用のテーブル (インデックスが個数に対応)
    const int scores[] = {0, 1, 10, 100};
    if( whiteCount == 0 )
    	return scores[blackCount];
    else
    	return -scores[whiteCount];
}
