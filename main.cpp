#include "mainwindow.h"
#include "qapplication.h"

int main(int argc, char *argv[])
{
    // For HighDPI screens
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    MainWindow window;

    window.show();
    return app.exec();
}
