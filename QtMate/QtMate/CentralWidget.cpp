#include <QPainter>
#include "CentralWidget.h"

void CentralWidget::paintEvent(QPaintEvent* event)
{
	//qDebug() << "CentralWidget::paintEvent(QPaintEvent* event)";
	QPainter painter(this);

	double ww = width();
    double wh = height();

    painter.fillRect(QRect(0, 0, ww, wh), QColor("#80c080"));
}
