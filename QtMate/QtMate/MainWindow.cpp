#include <QTimer>
#include "MainWindow.h"
#include "Board.h"
#include "BoardWidget.h"

Global g;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindowClass())
{
	ui->setupUi(this);
	menuBar()->hide();
	statusBar()->setStyleSheet(
		"QToolButton:disabled {"
		"	 color: #c0c0c0;"		 // 明るいグレー（デフォルトは #808080 くらい）
		"	 background-color: transparent;"
		"}"
	);
	//ui->mainToolBar->setFloatable(false);
	//ui->mainToolBar->setMovable(false);
	m_board = std::make_unique<Board>();
	ui->board->setBoard(m_board.get());
	setFixedSize(500, 800);
	setWindowTitle("QtMate (Ultimate Tic-Tac-Toe) Ver. 0.001");
	//ui->black->setStyleSheet("background-color: skyblue;");
	//ui->white->setStyleSheet("background-color: gray;");
	buildConnections();
	updateStartStopAction();
	updateNextColor();
}

MainWindow::~MainWindow()
{
	delete ui;
}
void MainWindow::buildConnections() {
	connect(ui->board, &BoardWidget::cellClicked, this, &MainWindow::onCellClicked);
	connect(ui->action_Start, &QAction::triggered, this, &MainWindow::onActionStart);
	connect(ui->action_Stop, &QAction::triggered, this, &MainWindow::onActionStop);
	connect(ui->action_Init, &QAction::triggered, this, &MainWindow::onActionInit);
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
	if( x < 0 || x >= BOARD9_WD || y < 0 || y >= BOARD9_WD )
		return;
	if( m_board->get_color(x, y) != EMPTY )
		return;
	if( !m_board->isValidLB(x/3, y/3) )
		return;
	if( !g.m_isGameActive )
		return;
	if( g.m_next == BLACK && g.m_blackPlayer == HUMAN ||
		g.m_next == WHITE && g.m_whitePlayer == HUMAN )
	{
		do_put(x, y);
	}
}
void MainWindow::do_put(int x, int y) {
	if( m_board->put_color(x, y, g.m_next) ) {
		onActionStop();		//	勝敗がついた場合
	} else {
		g.m_next = BLACK+WHITE - g.m_next;
	}
	auto ev = -m_board->eval(g.m_next);
	qDebug() << "eval = " << ev;
	ui->statusBar->showMessage(QString("eval = %1").arg(ev));
	g.m_lastX = x;
	g.m_lastY = y;
	updateNextColor();
	ui->board->update();
	if( g.m_isGameActive )
		nextTurn();
	else {
		ui->messLabel->setText(g.m_next == BLACK ? "O won." : "X won.");
	}
}
void MainWindow::updateStartStopAction() {
	if( g.m_isGameActive ) {
		ui->action_Start->setEnabled(false);
		ui->action_Stop->setEnabled(true);
		ui->action_Stop->setChecked(false);
	} else {
		ui->action_Stop->setEnabled(false);
		ui->action_Start->setEnabled(true);
		ui->action_Start->setChecked(false);
	}
}
void MainWindow::onActionStart() {
	qDebug() << "MainWindow::onActionStart()";
	g.m_isGameActive = true;
	updateStartStopAction();
	nextTurn();
}
void MainWindow::onActionStop() {
	qDebug() << "MainWindow::onActionStop()";
	g.m_isGameActive = false;
	updateStartStopAction();
}
void MainWindow::onActionInit() {
	qDebug() << "MainWindow::onActionInit()";
	g.init();
	m_board->init();
	ui->board->update();
	updateNextColor();
}
void MainWindow::onBlackPlayerChanged(int ix) {
	qDebug() << QString("MainWindow::onBlackPlayerChanged(%1)").arg(ix);
	g.m_blackPlayer = ix;
}
void MainWindow::onWhitePlayerChanged(int ix) {
	qDebug() << QString("MainWindow::onWhitePlayerChanged(%1)").arg(ix);
	g.m_whitePlayer = ix;
}
void MainWindow::nextTurn() {
	if( g.m_next == BLACK && g.m_blackPlayer == HUMAN ||
		g.m_next == WHITE && g.m_whitePlayer == HUMAN )
	{
		return;
	}
	QTimer::singleShot(100, this, &MainWindow::proceedTurn);
}
void MainWindow::proceedTurn() {
	if( g.m_next == BLACK && g.m_blackPlayer == HUMAN ||
		g.m_next == WHITE && g.m_whitePlayer == HUMAN )
	{
		return;
	}
	auto ix = m_board->sel_moveRandom();
	if( ix < 0 ) {
		return;
	}
	do_put(ix%BOARD9_WD, ix/BOARD9_WD);
}
