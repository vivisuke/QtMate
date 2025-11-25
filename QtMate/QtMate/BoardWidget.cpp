#include <QPainter>
#include "BoardWidget.h"

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

}
