#include "app.h"
#include <QDebug>
#include "exceptions.h"

bool App::notify(QObject *reciever, QEvent *event) {
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
};
