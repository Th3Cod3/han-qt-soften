#include "ui_mainwindow.h"
#include <QSplitter>

void Ui_MainWindow::setupUi(QMainWindow *MainWindow) {
  if (MainWindow->objectName().isEmpty()) {
    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
  }

  MainWindow->resize(800, 600);

  user = new UserWidget(MainWindow);
  user->setupUi();

  control = new ControlWidget(MainWindow);
  control->setupUi();

  QSplitter *splitter = new QSplitter(Qt::Vertical, MainWindow);
  splitter->addWidget(user);
  splitter->addWidget(control);

  MainWindow->setCentralWidget(splitter);

  setupText(MainWindow);
}

void Ui_MainWindow::setupText(QMainWindow *MainWindow) {
  MainWindow->setWindowTitle("Coffee Machine");

  user->setupText();
  control->setupText();
}
