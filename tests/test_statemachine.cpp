#include "qpushbutton.h"
#include "qtestcase.h"
#include "qtestsupport_widgets.h"
#include "statemachine.h"
#include "ui_mainwindow.h"
#include <QSignalSpy>
#include <QtTest/QtTest>

class TestStateMachine : public QObject {
  Q_OBJECT

private slots:
  void testInitialState();
  void testRequestCoffee();
  void testRequestErrorRecovery();
};

void TestStateMachine::testInitialState() {
  QMainWindow mainWindow;
  Ui_MainWindow ui;
  ui.setupUi(&mainWindow);

  StateMachine sm(&ui);
  mainWindow.show();
  QCoreApplication::processEvents();

  bool result = QTest::qWaitForWindowExposed(&mainWindow);
  QVERIFY2(result, "Window not exposed");

  QSet<QAbstractState*> states = sm.configuration();
  QCOMPARE(states.size(), 1);
  auto state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_off"));

  auto offBtn = ui.user->offBtn;
  QVERIFY2(offBtn != nullptr, "Off button not found");

  auto nextBtn = ui.control->nextBtn;
  QVERIFY2(nextBtn != nullptr, "Next button not found");
}

void TestStateMachine::testRequestCoffee() {
  QMainWindow mainWindow;
  Ui_MainWindow ui;
  ui.setupUi(&mainWindow);

  StateMachine sm(&ui);
  mainWindow.show();
  QCoreApplication::processEvents();

  bool result = QTest::qWaitForWindowExposed(&mainWindow);
  QVERIFY2(result, "Window not exposed");

  QSet<QAbstractState*> states = sm.configuration();
  QCOMPARE(states.size(), 1);
  auto state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_off"));

  auto offBtn = ui.user->offBtn;
  QVERIFY2(offBtn != nullptr, "Off button not found");
  offBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_startUp"));

  auto centerScreen = ui.user->centerLabel;
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->text().contains("Starting up"), 1000);

  auto screenOptions = ui.user->coffeOptionsLabel;
  QTRY_VERIFY_WITH_TIMEOUT(screenOptions->isVisible(), 4000);
  QTRY_VERIFY_WITH_TIMEOUT(screenOptions->text().contains("Select your coffee"), 1000);

  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_idle"));

  auto espressoBtn = ui.user->espressoBtn;
  QVERIFY2(espressoBtn != nullptr, "Espresso button not found");
  espressoBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_checkCup"));

  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->text().contains("Place cup"), 1000);

  auto nextBtn = ui.control->nextBtn;
  QVERIFY2(nextBtn != nullptr, "Next button not found");
  nextBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_heating"));

  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->text().contains("Heating water"), 1000);
  nextBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_grinding"));

  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->text().contains("Grinding coffee"), 1000);
  nextBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_brewing"));

  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->text().contains("Brewing coffee"), 1000);
  nextBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_cleaning"));

  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(centerScreen->text().contains("Cleaning"), 1000);
  nextBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_idle"));

  QTRY_VERIFY_WITH_TIMEOUT(screenOptions->isVisible(), 4000);
  QTRY_VERIFY_WITH_TIMEOUT(screenOptions->text().contains("Select your coffee"), 1000);
}

void TestStateMachine::testRequestErrorRecovery() {
  QMainWindow mainWindow;
  Ui_MainWindow ui;
  ui.setupUi(&mainWindow);

  StateMachine sm(&ui);
  mainWindow.show();
  QCoreApplication::processEvents();

  bool result = QTest::qWaitForWindowExposed(&mainWindow);
  QVERIFY2(result, "Window not exposed");

  QSet<QAbstractState*> states = sm.configuration();
  QCOMPARE(states.size(), 1);
  auto state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_off"));

  auto offBtn = ui.user->offBtn;
  QVERIFY2(offBtn != nullptr, "Off button not found");

  auto nextBtn = ui.control->nextBtn;
  QVERIFY2(nextBtn != nullptr, "Next button not found");

  auto espressoBtn = ui.user->espressoBtn;
  QVERIFY2(espressoBtn != nullptr, "Espresso button not found");

  offBtn->click();

  QCoreApplication::processEvents();
  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_startUp"));

  nextBtn->click();
  QCoreApplication::processEvents();

  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_idle"));

  espressoBtn->click();
  QCoreApplication::processEvents();

  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_checkCup"));

  nextBtn->click();
  QCoreApplication::processEvents();

  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_heating"));

  QTRY_VERIFY_WITH_TIMEOUT(ui.user->centerLabel->isVisible(), 1000);
  QTRY_VERIFY_WITH_TIMEOUT(ui.user->centerLabel->text().contains("Error contact support at"), 10000);

  QCoreApplication::processEvents();

  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_error"));

  nextBtn->click();
  QCoreApplication::processEvents();

  states = sm.configuration();
  QCOMPARE(states.size(), 1);
  state = *(states.begin());
  QCOMPARE(state->objectName(), QString("s_idle"));

  auto screenOptions = ui.user->coffeOptionsLabel;
  QTRY_VERIFY_WITH_TIMEOUT(screenOptions->isVisible(), 500);
  QTRY_VERIFY_WITH_TIMEOUT(screenOptions->text().contains("Select your coffee"), 500);
}

QTEST_MAIN(TestStateMachine)
#include "test_statemachine.moc"
