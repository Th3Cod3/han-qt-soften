#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  ui = new Ui_MainWindow;
  ui->setupUi(this);

  statemachine = new StateMachine(ui);
}

MainWindow::~MainWindow() {

}
