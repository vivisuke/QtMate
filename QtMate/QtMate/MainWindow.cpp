#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);
	setFixedSize(500, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

