#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include "controlwidget.h"
#include "qmainwindow.h"
#include "userwidget.h"

class Ui_MainWindow {
public:
  UserWidget *user;
  ControlWidget *control;

  void setupUi(QMainWindow *MainWindow);
  void setupText(QMainWindow *MainWindow);
};

#endif // UI_MAINWINDOW_H
