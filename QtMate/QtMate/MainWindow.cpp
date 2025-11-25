#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);
	setFixedSize(500, 800);
	setWindowTitle("QtMate (Ultimate Tic-Tac-Toe) Ver. 0.001");
}

MainWindow::~MainWindow()
{
    delete ui;
}

