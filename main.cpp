#include <QApplication>
#include <QObject>
#include <QDebug>
#include <iostream>
#include "reciever.h"
#include "exceptions.h"

class App : public QApplication {
  public:
  App(int &argc, char **argv) : QApplication(argc, argv) {};
  virtual ~App() {};
  virtual bool notify(QObject *reciever, QEvent *event) {
    try {
      QApplication::notify(reciever, event);
    }
    catch(int e) {
      qCritical() << "Exception raised. Code:" << e;
      quit();
    }
    catch(TRPCSessionException &e) {
      qCritical() << "Exception raised: " << e.message();
      quit();
    }
    catch(std::exception &e) {
      qCritical() << "Exception raised: " << e.what();
      quit();
    }
    return false;
  }
};

int main(int argc, char **argv) {
  App app(argc, argv);
  Reciever reciever("localhost");
  QObject::connect(&reciever, SIGNAL(term()), &app, SLOT(quit()));
  reciever.run();
  return app.exec();
};
