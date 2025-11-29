#pragma once
#include <QWidget>

class Board;

const int N_HORZ = 9;
const int MARGIN = 24;
const int CELL_WD = 48;


class BoardWidget : public QWidget
{
	Q_OBJECT

public:
	BoardWidget(QWidget *parent = nullptr) : QWidget(parent) {}

	void setBoard(Board *ptr) { m_board = ptr; }

protected:
	QPoint		xyToPoint(int x, int y) const {
		return QPoint(x*CELL_WD+MARGIN, y*CELL_WD+MARGIN);
	}
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
	void	cellClicked(int x, int y);
    
private:
    Board	*m_board = nullptr;
};

