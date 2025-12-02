#pragma once

#include <memory>           // std::unique_ptr
#include <QtWidgets/QMainWindow>
//#include <QTimer>
#include "ui_MainWindow.h"
//#include "Board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
	void	onCellClicked(int x, int y);
	void	onActionStart();
	void	onActionStop();
	void	onActionInit();
	void	onBlackPlayerChanged(int ix);
	void	onWhitePlayerChanged(int ix);

protected:
	void	buildConnections();
	void	updateStartStopAction();
	void	updateNextColor();
	void	nextTurn();				//	次の手番に（AI手番の場合は、500msec ウェイト
	void	proceedTurn();			//	次の手番を進める
	void	do_put(int x, int y);

private:
    Ui::MainWindowClass *ui;
    //QTimer	m_timer;
    std::unique_ptr<class Board> m_board;
};

