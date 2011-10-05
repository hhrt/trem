#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>

class TRPCSession;

class Reciever : public QObject {
  Q_OBJECT
  public:
  Reciever(const char *host = "localhost", const char *port = "9091", const char *url = "/transmission/rpc/");
  void run();
  private:
  TRPCSession *session;
  private slots:
  void success();
  signals:
  void term();
};

#endif
