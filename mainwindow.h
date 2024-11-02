#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmainwindow.h"
#include "statemachine.h"
#include "ui_mainwindow.h"

namespace Ui {
  class Ui_MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui_MainWindow *ui;
  StateMachine *statemachine;

  void setupStates();
};

#endif // MAINWINDOW_H
