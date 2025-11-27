#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/images/tic-tac-toe.png"));    // アイコンを設定（リソース or ファイルパス）

    MainWindow window;
    window.show();
    return app.exec();
}
