#include "controlwidget.h"

ControlWidget::ControlWidget(QMainWindow *parent) : QWidget(parent) {
}

void ControlWidget::setupUi() {
  this->setObjectName(QString::fromUtf8("controlDisplay"));

  nextBtn = new QPushButton();
  nextBtn->setObjectName("control->nextBtn");

  timeoutLabel = new QLabel();
  timeoutLabel->setObjectName("control->timeoutLabel");

  grid = new QGridLayout(this);
  grid->setObjectName("control->grid");

  grid->addWidget(timeoutLabel);
  grid->addWidget(nextBtn, 0, 1);
  setupText();
}

void ControlWidget::setupText() {
  nextBtn->setText("Next");
  timeoutLabel->setText("0");
}
