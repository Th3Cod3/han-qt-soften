#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "ui_mainwindow.h"
#include <QStateMachine>
#include <QTimer>

class StateMachine : public QStateMachine {
  Q_OBJECT

public:
  StateMachine(Ui_MainWindow *ui);

signals:
  void switchOff(void);
  void userRequest(void);
  void cupRemoved(void);
  void cupDetected(void);
  void cupPlaced(void);
  void waterHeating(void);
  void waterHeated(void);
  void coffeeGrinding(void);
  void weightReached(void);
  void coffeeBrewing(void);
  void volumeReached(void);
  void coffeeReady(void);

  void coffeeBeansEmpty(void);
  void waterEmpty(void);
  void timeout(void);

private slots:
  void offEntered(void);
  void offExited(void);
  void startUpEntered(void);
  void startUpExited(void);
  void idleEntered(void);
  void idleExited(void);
  void checkCupEntered(void);
  void checkCupExited(void);
  void heatingEntered(void);
  void heatingExited(void);
  void grindingEntered(void);
  void grindingExited(void);
  void brewingEntered(void);
  void brewingExited(void);
  void cleaningEntered(void);
  void cleaningExited(void);
  void errorEntered(void);
  void errorExited(void);
  void shutdownEntered(void);
  void shutdownExited(void);

  void tiggerTimeout(void);
  void updateState(void);

private:
  Ui_MainWindow *ui;
  QTimer *refreshTimer;
  QTimer *timer;

  void setupStates(void);
  void startUpRefresh(void);
  void shutdownRefresh(void);
};

#endif // STATEMACHINE_H
