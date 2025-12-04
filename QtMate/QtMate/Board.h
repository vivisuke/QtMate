#pragma once
#include <iostream>

enum {
	EMPTY = 0, BLACK = 1, WHITE = -BLACK,
	HUMAN = 0, RANDOM_AI,
};

const int BOARD_WD = 3;
const int BOARD_SIZE = BOARD_WD * BOARD_WD;
const int BOARD9_WD = 9;
const int BOARD9_SIZE = BOARD9_WD * BOARD9_WD;

using Color = char;
using uchar = unsigned char;

struct Global {
	bool	m_isGameActive = false;	//	ゲーム開始状態か？
	bool	m_thinkingAI = false;	//	AI 考慮中
	Color	m_next = BLACK;			//	次の手番
	//Color	m_winner = EMPTY;		//	勝者
	int		m_blackPlayer = 0;
	int		m_whitePlayer = 0;
	//int		m_lastX = -1;			//	直前着手位置
	//int		m_lastY = -1;			//	直前着手位置
public:
	void	init() {
		m_next = BLACK;
		//m_winner = EMPTY;
		//m_lastX = m_lastY = -1;
	}
};

struct UndoItem {
	int		m_x = 0;			//	着手位置
	int		m_y = 0;
	bool	m_gbChanged = false;	//	グローバルボードに石を打った
public:
	UndoItem(int x, int y=0, bool gbChanged = false)
		: m_x(x), m_y(y), m_gbChanged(gbChanged)
	{
	}
};

class Board
{
public:
	Board() {
		std::cout << "Board::Board()" << std::endl;
		init();
	}
	// コピーコンストラクタ
    Board(const Board& other)
        : m_winner(other.m_winner)
        , m_emptyGB(other.m_emptyGB)
    {
        // 固定サイズ配列は std::copy かループでコピー
        std::copy(std::begin(other.m_localBoard), std::end(other.m_localBoard), std::begin(m_localBoard));
        std::copy(std::begin(other.m_globalBoard), std::end(other.m_globalBoard), std::begin(m_globalBoard));
        std::copy(std::begin(other.m_nEmpty), std::end(other.m_nEmpty), std::begin(m_nEmpty));
        std::copy(std::begin(other.m_isValidLB), std::end(other.m_isValidLB), std::begin(m_isValidLB));
    }
	~Board() {
		std::cout << "Board::~Board()" << std::endl;
	}
public:
	void	init();
	Color	get_winner() const { return m_winner; }
	bool	put_color(int x, int y, Color col);			//	return: col の勝利か？
	Color	get_color(int x, int y) const { return m_localBoard[y*BOARD9_WD + x]; }
	Color	get_colorGB(int x, int y) const { return m_globalBoard[y*BOARD_WD + x]; }
	bool	isValidLB(int x, int y) const { return m_isValidLB[y*BOARD_WD + x]; }
	bool	isThree(int x, int y, Color col) const;			//	三目並んだか？
	bool	isThreeGB(int gx, int gy, Color col) const;		//	Global Board で三目並んだか？
	void	set_color(int x, int y, Color col) { m_localBoard[y*BOARD9_WD + x] = col; }
	void	set_colorGB(int x, int y, Color col) { m_globalBoard[y*BOARD_WD + x] = col; }
	void	updateIsValidLB(int x, int y);
	int		get_lastX() const;
	int		get_lastY() const;
	bool	canUndo() const;
	void	do_undo();
	int		eval(Color col) const;		//	引数側から見た評価値を返す
	void	swapBW();					//	盤面黒白反転

	int		sel_moveRandom() const;
	int		sel_moveAB(Color col);

protected:
	int		evalLine(int ix, int d) const;		//	ローカルボードの１ライン評価
	int		evalLineGB(int ix, int d) const;	//	グローバルボードの１ライン評価

private:
	Color	m_winner = EMPTY;		//	勝者
	int		m_emptyGB = 9;			//	グローバルボード空セル数
	Color	m_localBoard[BOARD9_SIZE];
	Color	m_globalBoard[BOARD_SIZE];
	uchar	m_nEmpty[BOARD_SIZE];			//	各ローカルボード空欄数
	bool	m_isValidLB[BOARD_SIZE];		//	各ローカルボードに着手可能か？
    std::vector<UndoItem>	m_undoStack;			//	
};

