#pragma once

#include <memory>           // std::unique_ptr
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    std::unique_ptr<Board> m_board;
};

