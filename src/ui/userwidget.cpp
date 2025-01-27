#include "userwidget.h"
#include "qnamespace.h"
#include <QSplitter>

UserWidget::UserWidget(QMainWindow *parent) : QWidget(parent) {
}

void UserWidget::setupUi() {
  this->setStyleSheet("color: #ffffff; background-color: #000000;");

  grid = new QGridLayout(this);
  grid->setRowStretch(0, 1);
  grid->setColumnStretch(0, 1);
  grid->setObjectName("user->grid");

  frame = new QWidget();
  frame->setObjectName("user->frame");

  offBtn = new QPushButton();
  offBtn->setObjectName("user->offBtn");

  frameGrid = new QGridLayout();
  frameGrid->setObjectName("user->frameGrid");

  centerLabel = new QLabel();
  centerLabel->setObjectName("user->centerLabel");
  centerLabel->setAlignment(Qt::AlignCenter);

  espressoBtn = new QPushButton();
  espressoBtn->setObjectName("user->espressoBtn");
  coffeeBtn = new QPushButton();
  coffeeBtn->setObjectName("user->coffeeBtn");
  waterBtn = new QPushButton();
  waterBtn->setObjectName("user->waterBtn");
  coffeOptionsLabel = new QLabel();
  coffeOptionsLabel->setObjectName("user->coffeOptionsLabel");

  frameGrid->addWidget(coffeOptionsLabel, 0, 0, 1, 3);
  frameGrid->addWidget(espressoBtn, 1 , 0);
  frameGrid->addWidget(coffeeBtn, 1, 1);
  frameGrid->addWidget(waterBtn, 1, 2);
  frameGrid->addWidget(centerLabel, 0, 0, 1, 3);
  frame->setLayout(frameGrid);
  frame->setStyleSheet("color: #000000;");

  grid->addWidget(frame, 0, 0);
  grid->addWidget(offBtn, 1, 1, Qt::AlignBottom | Qt::AlignRight);
  hideOptions();
  hideText();

  setupText();
}

void UserWidget::setupText() {
  offBtn->setText("Off/On");
  coffeOptionsLabel->setText("Select your coffee");
  espressoBtn->setText("Espresso");
  coffeeBtn->setText("Coffee");
  waterBtn->setText("Water");
}

void UserWidget::showText() {
  hideOptions();
  centerLabel->show();
}

void UserWidget::hideText() {
  centerLabel->hide();
}

void UserWidget::showOptions() {
  hideText();
  espressoBtn->show();
  coffeeBtn->show();
  waterBtn->show();
  coffeOptionsLabel->show();
}

void UserWidget::hideOptions() {
  espressoBtn->hide();
  coffeeBtn->hide();
  waterBtn->hide();
  coffeOptionsLabel->hide();
}
