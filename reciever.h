#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>

class TRPCSession;

class Reciever : public QObject {
  Q_OBJECT
  public:
  Reciever(char *host = "localhost", char *port = "9091", char *url = "/transmission/rpc/");
  void run();
  private:
  TRPCSession *session;
  private slots:
  void err(int errorCode);
  void success();
  signals:
  void term();
};

#endif
