#include "MainWindow.h"
#include "Board.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);
    m_board = std::make_unique<Board>();
    ui->board->setBoard(m_board.get());
	setFixedSize(500, 800);
	setWindowTitle("QtMate (Ultimate Tic-Tac-Toe) Ver. 0.001");
	ui->black->setStyleSheet("border-bottom: 6px solid yellow;");
	ui->white->setStyleSheet("border-bottom: 6px solid yellow;");
	//ui->black->setStyleSheet("background-color: skyblue;");
	//ui->white->setStyleSheet("background-color: gray;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

