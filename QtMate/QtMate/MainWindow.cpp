#include "MainWindow.h"
#include "Board.h"
#include "BoardWidget.h"

Global g;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);
    m_board = std::make_unique<Board>();
    ui->board->setBoard(m_board.get());
	setFixedSize(500, 800);
	setWindowTitle("QtMate (Ultimate Tic-Tac-Toe) Ver. 0.001");
	//ui->black->setStyleSheet("background-color: skyblue;");
	//ui->white->setStyleSheet("background-color: gray;");
	buildConnections();
	updateNextColor();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::buildConnections() {
	connect(ui->board, &BoardWidget::cellClicked, this, &MainWindow::onCellClicked);
}

void MainWindow::updateNextColor() {
	if( g.m_next == BLACK ) {
		ui->black->setStyleSheet("border-bottom: 6px solid yellow;");
		ui->white->setStyleSheet("border-bottom: 6px solid transparent;");
		ui->messLabel->setText("O's turn");
	} else {
		ui->black->setStyleSheet("border-bottom: 6px solid transparent;");
		ui->white->setStyleSheet("border-bottom: 6px solid yellow;");
		ui->messLabel->setText("X's turn");
	}
}

void MainWindow::onCellClicked(int x, int y) {
	qDebug() << QString("MainWindow::onCellClicked(%1, %2)").arg(x).arg(y);
	g.m_next = BLACK+WHITE - g.m_next;
	updateNextColor();
}
