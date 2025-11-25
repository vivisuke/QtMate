#pragma once
#include "C:\Qt\6.10.0\msvc2022_64\include\QtWidgets\qwidget.h"
class CentralWidget : public QWidget
{
public:
	CentralWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent* event) override;

};

