#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include "qgridlayout.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

class ControlWidget : public QWidget {
public:
  ControlWidget(QMainWindow *parent = nullptr);
  QGridLayout *grid;
  QPushButton *nextBtn;
  QLabel *timeoutLabel;

  void setupUi();
  void setupText();
};

#endif // CONTROL_WIDGET_H
