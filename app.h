#ifndef APP_H
#define APP_H

#include <QApplication>

class App : public QApplication {
  Q_OBJECT
  public:
  App(int &argc, char **argv, QApplication::Type type) : QApplication(argc, argv, type) {};
  virtual ~App() {};
  virtual bool notify(QObject *reciever, QEvent *event);
};

#endif
