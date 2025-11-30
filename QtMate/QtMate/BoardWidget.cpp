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

    qDebug() << "Attempting to load image from:" << imageOPath;

    if (!m_image_o.load(imageOPath)) {
        qDebug() << "can't load " << imageOPath;
    }
    if (!m_image_x.load(imageXPath)) {
        qDebug() << "can't load " << imageXPath;
    }
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

    for(int i = 1; i < N_HORZ; ++i) {
        if (i % 3 == 0) {
            pen.setWidth(4);                    // 線幅 px
        } else {
            pen.setWidth(1);                    // 線幅 px
        }
        painter.setPen(pen);
        painter.drawLine(xyToPoint(0, i), xyToPoint(N_HORZ, i));
	    painter.drawLine(xyToPoint(i, 0), xyToPoint(i, N_HORZ));
    }

	painter.setPen(Qt::white);                                   // 文字色
	painter.setFont(QFont("Meiryo UI", 12, QFont::Bold));
    for(int x = 0; x < N_HORZ; ++x) {
	    painter.drawText(xyToPoint(x, 0) + QPointF(CELL_WD*0.35, -6), QChar('a'+x));
    }
    for(int y = 0; y < N_HORZ; ++y) {
	    painter.drawText(xyToPoint(0, y+1) + QPointF(-CELL_WD*0.35, -CELL_WD*0.3), QChar('1'+y));
	    //painter.drawText(xyToPoint(0, y+1) + QPointF(-CELL_WD*0.5, -CELL_WD*0.3), QString::number(y + 1).rightJustified(2));
    }

    //painter.drawImage(xyToPoint(1, 1), m_image_o);
    //painter.drawImage(xyToPoint(4, 3), m_image_x);
    for(int y = 0; y < N_HORZ; ++y) {
	    for(int x = 0; x < N_HORZ; ++x) {
	    	auto col = m_board->get_color(x, y);
			if( col == BLACK )
			    painter.drawImage(xyToPoint(x, y), m_image_o);
			else if( col == WHITE )
			    painter.drawImage(xyToPoint(x, y), m_image_x);
	    }
    }
}
void BoardWidget::mousePressEvent(QMouseEvent *event) {
	qDebug() << "mousePressEvent(QMouseEvent *event)";
	QPoint pos = event->pos();
	int x = (pos.x() - MARGIN) / CELL_WD;
	int y = (pos.y() - MARGIN) / CELL_WD;
	emit cellClicked(x, y);
}
