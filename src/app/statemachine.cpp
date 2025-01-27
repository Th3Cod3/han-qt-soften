#include "statemachine.h"
#include "QSignalTransition"
#include "qpushbutton.h"
#include "qset.h"

#define STATE_DEFAULT_TIMEOUT 8000
#define STATE_SHORT_TIMEOUT 2000

StateMachine::StateMachine(Ui_MainWindow *ui) {
  this->ui = ui;

  timer = new QTimer();
  timer->setSingleShot(true);

  refreshTimer = new QTimer();
  refreshTimer->setInterval(250);

  setupStates();
}

void StateMachine::setupStates() {
  QState *s_off = new QState();
  s_off->setObjectName("s_off");
  QState *s_startUp = new QState();
  s_startUp->setObjectName("s_startUp");
  QState *s_idle = new QState();
  s_idle->setObjectName("s_idle");
  QState *s_checkCup = new QState();
  s_checkCup->setObjectName("s_checkCup");
  QState *s_heating = new QState();
  s_heating->setObjectName("s_heating");
  QState *s_grinding = new QState();
  s_grinding->setObjectName("s_grinding");
  QState *s_brewing = new QState();
  s_brewing->setObjectName("s_brewing");
  QState *s_cleaning = new QState();
  s_cleaning->setObjectName("s_cleaning");
  QState *s_error = new QState();
  s_error->setObjectName("s_error");
  QState *s_shutdown = new QState();
  s_shutdown->setObjectName("s_shutdown");

  this->addState(s_off);
  this->addState(s_startUp);
  this->addState(s_idle);
  this->addState(s_checkCup);
  this->addState(s_heating);
  this->addState(s_grinding);
  this->addState(s_brewing);
  this->addState(s_cleaning);
  this->addState(s_error);
  this->addState(s_shutdown);
  this->setInitialState(s_off);

  s_off->addTransition(ui->user->offBtn, &QPushButton::clicked, s_startUp)->setObjectName("offBtn->click=s_startUp");

  s_startUp->addTransition(ui->user->offBtn, &QPushButton::clicked, s_off)->setObjectName("offBtn->click=s_off");
  s_startUp->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_idle)->setObjectName("nextBtn->click=s_idle");
  s_startUp->addTransition(this, &StateMachine::timeout, s_idle)->setObjectName("timeout=s_idle");

  s_idle->addTransition(ui->user->offBtn, &QPushButton::clicked, s_shutdown)->setObjectName("offBtn->click=s_shutdown");
  s_idle->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_checkCup)->setObjectName("nextBtn->click=s_checkCup");
  s_idle->addTransition(ui->user->espressoBtn, &QPushButton::clicked, s_checkCup)->setObjectName("espressoBtn->click=s_checkCup");
  s_idle->addTransition(ui->user->coffeeBtn, &QPushButton::clicked, s_checkCup)->setObjectName("coffeeBtn->click=s_checkCup");
  s_idle->addTransition(ui->user->waterBtn, &QPushButton::clicked, s_checkCup)->setObjectName("waterBtn->click=s_checkCup");

  s_checkCup->addTransition(this, &StateMachine::cupRemoved, s_error)->setObjectName("cupRemoved=s_error");
  s_checkCup->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_heating)->setObjectName("nextBtn->click=s_heating");
  s_checkCup->addTransition(this, &StateMachine::timeout, s_idle)->setObjectName("timeout=s_idle");

  s_heating->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_grinding)->setObjectName("nextBtn->click=s_grinding");
  s_heating->addTransition(this, &StateMachine::timeout, s_error)->setObjectName("timeout=s_error");
  s_heating->addTransition(this, &StateMachine::waterEmpty, s_error)->setObjectName("waterEmpty=s_error");
  s_heating->addTransition(this, &StateMachine::cupRemoved, s_error)->setObjectName("cupRemoved=s_error");

  s_grinding->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_brewing)->setObjectName("nextBtn->click=s_brewing");
  s_grinding->addTransition(this, &StateMachine::timeout, s_error)->setObjectName("timeout=s_error");
  s_grinding->addTransition(this, &StateMachine::coffeeBeansEmpty, s_error)->setObjectName("coffeeBeansEmpty=s_error");

  s_brewing->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_cleaning)->setObjectName("nextBtn->click=s_cleaning");
  s_brewing->addTransition(this, &StateMachine::timeout, s_error)->setObjectName("timeout=s_error");
  s_brewing->addTransition(this, &StateMachine::cupRemoved, s_error)->setObjectName("cupRemoved=s_error");

  s_cleaning->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_idle)->setObjectName("nextBtn->click=s_idle");
  s_cleaning->addTransition(this, &StateMachine::timeout, s_error)->setObjectName("timeout=s_error");
  s_cleaning->addTransition(this, &StateMachine::waterEmpty, s_error)->setObjectName("waterEmpty=s_error");

  s_shutdown->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_off)->setObjectName("nextBtn->click=s_off");
  s_shutdown->addTransition(this, &StateMachine::timeout, s_off)->setObjectName("timeout=s_off");

  s_error->addTransition(ui->control->nextBtn, &QPushButton::clicked, s_idle)->setObjectName("nextBtn->click=s_idle");

  connect(s_off, &QState::entered, this, &StateMachine::offEntered);
  connect(s_off, &QState::exited, this, &StateMachine::offExited);
  connect(s_startUp, &QState::exited, this, &StateMachine::startUpExited);
  connect(s_startUp, &QState::entered, this, &StateMachine::startUpEntered);
  connect(s_idle, &QState::entered, this, &StateMachine::idleEntered);
  connect(s_idle, &QState::exited, this, &StateMachine::idleExited);
  connect(s_checkCup, &QState::entered, this, &StateMachine::checkCupEntered);
  connect(s_checkCup, &QState::exited, this, &StateMachine::checkCupExited);
  connect(s_heating, &QState::entered, this, &StateMachine::heatingEntered);
  connect(s_heating, &QState::exited, this, &StateMachine::heatingExited);
  connect(s_grinding, &QState::entered, this, &StateMachine::grindingEntered);
  connect(s_grinding, &QState::exited, this, &StateMachine::grindingExited);
  connect(s_brewing, &QState::entered, this, &StateMachine::brewingEntered);
  connect(s_brewing, &QState::exited, this, &StateMachine::brewingExited);
  connect(s_cleaning, &QState::entered, this, &StateMachine::cleaningEntered);
  connect(s_cleaning, &QState::exited, this, &StateMachine::cleaningExited);
  connect(s_error, &QState::entered, this, &StateMachine::errorEntered);
  connect(s_error, &QState::exited, this, &StateMachine::errorExited);
  connect(s_shutdown, &QState::entered, this, &StateMachine::shutdownEntered);
  connect(s_shutdown, &QState::exited, this, &StateMachine::shutdownExited);

  connect(timer, &QTimer::timeout, this, &StateMachine::tiggerTimeout);
  connect(refreshTimer, &QTimer::timeout, this, &StateMachine::updateState);

  this->start();
  refreshTimer->start();
}

void StateMachine::tiggerTimeout() { emit timeout(); }

void StateMachine::updateState() {
  ui->control->timeoutLabel->setText("Timeout: " + QString::number(timer->remainingTime() / 1000) + "s");

  QSet<QAbstractState *> activeStates = this->configuration();
  for (QAbstractState *state : activeStates) {
    if (state->objectName() == "s_startUp") {
      startUpRefresh();
    } else if (state->objectName() == "s_shutdown") {
      shutdownRefresh();
    }
  }
}

void StateMachine::offEntered() {
  ui->user->hideText();
  ui->user->offBtn->setStyleSheet("background-color: #ff0000;");
  ui->user->frame->setStyleSheet("background-color: #000000;");
}

void StateMachine::offExited() {}

void StateMachine::startUpEntered() {
  ui->user->frame->setStyleSheet("background-color: #cccccc;");
  ui->user->centerLabel->setStyleSheet("color: #000000;");
  ui->user->showText();
  ui->user->offBtn->setStyleSheet("background-color: #00ff00;");
  timer->start(STATE_SHORT_TIMEOUT);
}

void StateMachine::startUpRefresh() {
  float dots = (timer->remainingTime() / 500) % 3;
  dots = 3 - dots;
  QString text = "Starting up";

  for (int i = 0; i < dots; i++) {
    text += ".";
  }

  ui->user->centerLabel->setText(text);
}

void StateMachine::startUpExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::idleEntered() { 
  ui->user->showOptions();
}

void StateMachine::idleExited() { 
  ui->user->hideOptions();
}

void StateMachine::checkCupEntered() {
  ui->user->centerLabel->setText("Place cup");
  ui->user->centerLabel->setStyleSheet("color: #000000;");
  ui->user->showText();
  timer->start(STATE_DEFAULT_TIMEOUT);
}

void StateMachine::checkCupExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::heatingEntered() {
  ui->user->centerLabel->setText("Heating water");
  ui->user->centerLabel->setStyleSheet("color: #0000ff;");
  ui->user->showText();
  timer->start(STATE_DEFAULT_TIMEOUT);
}

void StateMachine::heatingExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::grindingEntered() {
  ui->user->centerLabel->setText("Grinding coffee");
  ui->user->centerLabel->setStyleSheet("color: #000000;");
  ui->user->showText();
  timer->start(STATE_DEFAULT_TIMEOUT);
}

void StateMachine::grindingExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::brewingEntered() {
  ui->user->centerLabel->setText("Brewing coffee");
  ui->user->centerLabel->setStyleSheet("color: #000000;");
  ui->user->showText();
  timer->start(STATE_DEFAULT_TIMEOUT);
}

void StateMachine::brewingExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::cleaningEntered() {
  ui->user->centerLabel->setText("Cleaning");
  ui->user->centerLabel->setStyleSheet("color: #000000;");
  ui->user->showText();
  timer->start(STATE_DEFAULT_TIMEOUT);
}

void StateMachine::cleaningExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::errorEntered() {
  ui->user->centerLabel->setText("Error contact support at 1234567890");
  ui->user->centerLabel->setStyleSheet("color: #ff0000;");
  ui->user->showText();
  timer->start(STATE_DEFAULT_TIMEOUT);
}

void StateMachine::errorExited() {
  timer->stop();
  ui->user->hideText();
}

void StateMachine::shutdownEntered() {
  timer->start(STATE_SHORT_TIMEOUT);
}

void StateMachine::shutdownRefresh() {
  float dots = (timer->remainingTime() / 500) % 3;
  dots = 3 - dots;
  QString text = "Shutting down";

  for (int i = 0; i < dots; i++) {
    text += ".";
  }

  ui->user->centerLabel->setText(text);
}

void StateMachine::shutdownExited() {
  timer->stop();
}
