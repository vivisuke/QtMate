#include <vector>
#include <random>
#include "Board.h"
#include <QDebug>

using namespace std;

static std::random_device rd;
static std::mt19937 rgen(rd()); 
//static std::mt19937 rgen(0); 
//std::mt19937_64 rgen64(rd());		// 64ビット版

#define		is_empty()	empty()

void Board::init() {
	m_next = BLACK;
	m_forcedLB = -1;
	m_winner = EMPTY;
	m_emptyGB = BOARD_SIZE;
	for(auto& v: m_localBoard) v = EMPTY;
	for(auto& v: m_globalBoard) v = EMPTY;
	//for(auto& v: m_isValidLB) v = true;
	for(auto& v: m_nEmptyLB) v = BOARD_SIZE;
	m_undoStack.clear();
}
void Board::updateIsValidLB(int x, int y) {				//	次に着手可能ローカルボードかどうかを判定
	int ix = (y%BOARD_WD)*BOARD_WD + (x%BOARD_WD);
	if( m_globalBoard[ix] == EMPTY && m_nEmptyLB[ix] != 0 ) {
		//for(auto& v: m_isValidLB) v = false;
		//m_isValidLB[ix] = true;
		m_forcedLB = ix;
	} else {
		//for(auto& v: m_isValidLB) v = true;
		m_forcedLB = -1;
	}
}
bool Board::put_color(int x, int y, Color col) {
	bool won = false;
	UndoItem ui(x, y);
	set_color(x, y, col);
	m_nEmptyLB[(y/3)*3 + x/3] -= 1;
	if( get_colorGB(x/3, y/3) == EMPTY && isThree(x, y, col) ) {
		ui.m_gbChanged = true;
		set_colorGB(x/3, y/3, col);
		won = isThreeGB(x/3, y/3, col);
		if( won )
			m_winner = col;
	}
	ui.m_forcedLB = m_forcedLB;
	m_undoStack.push_back(ui);
	updateIsValidLB(x, y);
	if( !won )
		m_next = BLACK + WHITE - m_next;
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
			if( isValidLB(x/3, y/3) && get_color(x, y) == EMPTY ) {
				lst.push_back(y * BOARD9_WD + x);
			}
		}
	}
	if( lst.is_empty() ) return -1;
	return lst[rgen() % lst.size()];
}
int Board::sel_moveAB(Color col, int depth) {
	vector<int> lst;
	for(int y = 0; y < BOARD9_WD; ++y) {
		for(int x = 0; x < BOARD9_WD; ++x) {
			if( isValidLB(x/3, y/3) && get_color(x, y) == EMPTY ) {
				lst.push_back(y * BOARD9_WD + x);
			}
		}
	}
	if( lst.is_empty() ) return -1;
	Board bd(*this);
	//if( col == WHITE ) bd.swapBW();
	int maxev = -99999;
	int bestix = -1;
	for(auto ix: lst) {
		bd.put_color(ix%BOARD9_WD, ix/BOARD9_WD, col);
		int ev = bd.eval(col);
		qDebug() << "ix = " << ix << ", eval = " << ev;
		bd.do_undo();
		if( ev > maxev ) {
			maxev = ev;
			bestix = ix;
		}
	}
	//if( col == WHITE ) bd.swapBW();
	return bestix;
}
#if 0
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
#endif
int Board::evalLine(int ix, int d) const {
    int blackCount = 0;
    int whiteCount = 0;
    if( m_localBoard[ix] == BLACK ) blackCount+= 1;
    else if( m_localBoard[ix] == WHITE ) whiteCount+= 1;
    if( m_localBoard[ix+d] == BLACK ) blackCount+= 1;
    else if( m_localBoard[ix+d] == WHITE ) whiteCount+= 1;
    if( m_localBoard[ix+2*d] == BLACK ) blackCount+= 1;
    else if( m_localBoard[ix+2*d] == WHITE ) whiteCount+= 1;

    if( blackCount != 0 && whiteCount != 0 ) return 0;
	// スコア変換用のテーブル (インデックスが個数に対応)
    const int scores[] = {0, 1, 10, 100};
    if( whiteCount == 0 )
    	return scores[blackCount];
    else
    	return -scores[whiteCount];
}
int Board::evalLineGB(int ix, int d) const {
    int blackCount = 0;
    int whiteCount = 0;
    if( m_globalBoard[ix] == BLACK ) blackCount+= 1;
    else if( m_globalBoard[ix] == WHITE ) whiteCount+= 1;
    if( m_globalBoard[ix+d] == BLACK ) blackCount+= 1;
    else if( m_globalBoard[ix+d] == WHITE ) whiteCount+= 1;
    if( m_globalBoard[ix+2*d] == BLACK ) blackCount+= 1;
    else if( m_globalBoard[ix+2*d] == WHITE ) whiteCount+= 1;

    if( blackCount != 0 && whiteCount != 0 ) return 0;
	// スコア変換用のテーブル (インデックスが個数に対応)
    const int scores[] = {0, 100, 1000, 10000};
    if( whiteCount == 0 )
    	return scores[blackCount];
    else
    	return -scores[whiteCount];
}
int Board::eval(Color col) const {		//	col から見た評価値を返す
	int ev = 0;
	//	まず先手がわからみた評価値を計算し、最後に col からみた評価値に変換
	//	ローカルボード評価
	for(int y = 0; y < 3; ++y) {
		for(int x = 0; x < 3; ++x) {
			if( m_globalBoard[y*3 + x] == EMPTY ) {		//	ローカルボードで３目並んでいない場合
				int ix = y*3*BOARD9_WD + x*3;		//	左上位置
				for(int i = 0; i < 3; ++i) {
					ev += evalLine(ix+i, BOARD9_WD);
					ev += evalLine(ix+i*BOARD9_WD, 1);
				}
				ev += evalLine(ix, BOARD9_WD+1);
				ev += evalLine(ix+BOARD9_WD*2, -BOARD9_WD+1);
			}
		}
	}
	//	グローバルボード評価
	for(int i = 0; i < 3; ++i) {
		ev += evalLineGB(i, BOARD_WD);
		ev += evalLineGB(i*BOARD_WD, 1);
	}
	ev += evalLineGB(0, BOARD_WD+1);
	ev += evalLineGB(BOARD_WD*2, -BOARD_WD+1);
	//	undone: 勝敗がついた場合、空欄数を考慮
	if( ev > 9000 ) {
		ev = 10000 + get_nEmpty() * 100;
	} else if( ev < -9000 ) {
		ev = -10000 - get_nEmpty() * 100;
	}
	return col == BLACK ? ev : -ev;
}
int Board::get_nEmpty() const {
	int sum = 0;
	for(auto n: m_nEmptyLB) sum += n;
	return sum;
}
int Board::get_lastX() const {
	if( m_undoStack.is_empty() ) return -1;
	return m_undoStack.back().m_x;
}
int Board::get_lastY() const {
	if( m_undoStack.is_empty() ) return -1;
	return m_undoStack.back().m_y;
}
bool Board::canUndo() const {
	return !m_undoStack.is_empty();
}
void Board::do_undo() {
	if( m_undoStack.is_empty() ) return;
	UndoItem ui = m_undoStack.back();
	m_undoStack.pop_back();
	set_color(ui.m_x, ui.m_y, EMPTY);
	m_nEmptyLB[(ui.m_y/3)*3 + (ui.m_x/3)] += 1;
	m_forcedLB = ui.m_forcedLB;
	m_next = BLACK + WHITE - m_next;		//	パスは無い
	if( ui.m_gbChanged ) {
		set_colorGB(ui.m_x/3, ui.m_y/3, EMPTY);
	}
}
void Board::swapBW() {		//	盤面黒白反転
	for(auto& v: m_localBoard) v = -v;
	for(auto& v: m_globalBoard) v = -v;
}
