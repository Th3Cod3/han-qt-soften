#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

class UserWidget : public QWidget {
public:
  UserWidget(QMainWindow *parent = nullptr);
  QWidget *frame;
  QGridLayout *grid;
  QPushButton *offBtn;

  QGridLayout *frameGrid;
  QLabel *centerLabel;

  QPushButton *espressoBtn;
  QPushButton *coffeeBtn;
  QPushButton *waterBtn;
  QLabel *coffeOptionsLabel;

  void showText(void);
  void hideText(void);
  void showOptions(void);
  void hideOptions(void);
  void setupUi(void);
  void setupText(void);
};

#endif // USER_WIDGET_H
