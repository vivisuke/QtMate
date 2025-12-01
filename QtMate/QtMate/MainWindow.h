#pragma once

#include <memory>           // std::unique_ptr
#include <QtWidgets/QMainWindow>
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
	void buildConnections();
	void	updateNextColor();

private:
    Ui::MainWindowClass *ui;
    std::unique_ptr<class Board> m_board;
};

