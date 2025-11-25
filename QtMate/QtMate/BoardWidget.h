#pragma once
#include <QWidget>

class BoardWidget : public QWidget
{
	Q_OBJECT

public:
	BoardWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent* event) override;
};

