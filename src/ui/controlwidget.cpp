#include "controlwidget.h"

ControlWidget::ControlWidget(QMainWindow *parent) : QWidget(parent) {
}

void ControlWidget::setupUi() {
  this->setObjectName(QString::fromUtf8("controlDisplay"));

  nextBtn = new QPushButton();

  timeoutLabel = new QLabel();

  grid = new QGridLayout(this);

  grid->addWidget(timeoutLabel);
  grid->addWidget(nextBtn, 0, 1);
  setupText();
}

void ControlWidget::setupText() {
  nextBtn->setText("Next");
  timeoutLabel->setText("0");
}
