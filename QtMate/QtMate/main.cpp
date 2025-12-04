#include "MainWindow.h"
#include <QtWidgets/QApplication>
//#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setStyle(QStyleFactory::create("Fusion"));

    app.setWindowIcon(QIcon(":/images/tic-tac-toe.png"));    // アイコンを設定（リソース or ファイルパス）

    MainWindow window;
    window.show();
    return app.exec();
}
