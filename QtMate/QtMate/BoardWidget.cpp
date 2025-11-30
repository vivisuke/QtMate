#include <QPainter>
#include <QMouseEvent>
#include <QDir.h>
#include "Board.h"
#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
	QString currentPath = QDir::currentPath(); // または QCoreApplication::applicationDirPath();
    QString imageOPath = currentPath + "/images/circle_black_48.png";
    QString imageXPath = currentPath + "/images/close_black_48.png";
    QString imageBigOPath = currentPath + "/images/big_circle_black.png";
    QString imageBigXPath = currentPath + "/images/big_close_black.png";

    qDebug() << "Attempting to load image from:" << imageOPath;

    if (!m_imageO.load(imageOPath)) {
        qDebug() << "can't load " << imageOPath;
    }
    if (!m_imageX.load(imageXPath)) {
        qDebug() << "can't load " << imageXPath;
    }
    m_imageBigO.load(imageBigOPath);
    m_imageBigX.load(imageBigXPath);
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
	qDebug() << "BoardWidget::paintEvent(QPaintEvent* event)";
	QPainter painter(this);

	double ww = width();
    double wh = height();

    QPen pen;
    pen.setWidth(1);                    // 線幅 1px
    pen.setColor(Qt::black);            // 黒線
    painter.setPen(pen);
    //painter.drawLine(QPoint(0, 0), QPoint(ww, wh));

    painter.fillRect(QRect(0, 0, ww, wh), Qt::black);
    painter.fillRect(QRect(24, 24, 48*9, 48*9), QColor("#f0f0f0"));

    //	グリッド描画
    for(int i = 1; i < N_HORZ; ++i) {
        //if (i % 3 == 0) {
        //    pen.setWidth(4);                    // 線幅 px
        //} else {
        //    pen.setWidth(1);                    // 線幅 px
        //}
        //painter.setPen(pen);
        painter.drawLine(xyToPoint(0, i), xyToPoint(N_HORZ, i));
	    painter.drawLine(xyToPoint(i, 0), xyToPoint(i, N_HORZ));
    }
	//	盤面座標値描画
	painter.setPen(Qt::white);                                   // 文字色
	painter.setFont(QFont("Meiryo UI", 12, QFont::Bold));
    for(int x = 0; x < N_HORZ; ++x) {
	    painter.drawText(xyToPoint(x, 0) + QPointF(CELL_WD*0.35, -6), QChar('a'+x));
    }
    for(int y = 0; y < N_HORZ; ++y) {
	    painter.drawText(xyToPoint(0, y+1) + QPointF(-CELL_WD*0.35, -CELL_WD*0.3), QChar('1'+y));
	    //painter.drawText(xyToPoint(0, y+1) + QPointF(-CELL_WD*0.5, -CELL_WD*0.3), QString::number(y + 1).rightJustified(2));
    }
	//	盤面上石描画
    for(int y = 0; y < N_HORZ; ++y) {
	    for(int x = 0; x < N_HORZ; ++x) {
	    	auto col = m_board->get_color(x, y);
			if( col == BLACK )
			    painter.drawImage(xyToPoint(x, y), m_imageO);
			else if( col == WHITE )
			    painter.drawImage(xyToPoint(x, y), m_imageX);
	    }
    }
    //	グローバル盤面上石描画
    painter.drawImage(xyToPoint(0, 0), m_imageBigO);
    painter.drawImage(xyToPoint(3, 0), m_imageBigX);

    //	着手不可ローカルボードをグレイアウト
    for(int y = 0; y < BOARD_WD; ++y) {
	    for(int x = 0; x < BOARD_WD; ++x) {
	    	if( !m_board->isValidLB(x, y) ) {
			    painter.fillRect(QRect(xyToPoint(x*3, y*3), QSize(CELL_WD*3, CELL_WD*3)), QColor("#80808040"));
	    	}
	    }
    }
    //	グローバルボードグリッド描画
    pen.setWidth(4);                    // 線幅 px
    painter.setPen(pen);
    for(int i = 3; i < N_HORZ; i+=3) {
        painter.drawLine(xyToPoint(0, i), xyToPoint(N_HORZ, i));
	    painter.drawLine(xyToPoint(i, 0), xyToPoint(i, N_HORZ));
    }
}
void BoardWidget::mousePressEvent(QMouseEvent *event) {
	qDebug() << "mousePressEvent(QMouseEvent *event)";
	QPoint pos = event->pos();
	int x = (pos.x() - MARGIN) / CELL_WD;
	int y = (pos.y() - MARGIN) / CELL_WD;
	emit cellClicked(x, y);
}
