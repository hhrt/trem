#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QList>
#include "defines.h"

class TRPCSession;

class Reciever : public QObject {
  Q_OBJECT
  public:
  Reciever(const char *host = "localhost", const char *port = "9091", const char *url = "/transmission/rpc/");
  ~Reciever();
  void run(int actionCode = GetTorrentsList, QList<unsigned int> *ids = NULL);
  private:
  TRPCSession *session;
  void torrentsList() const;
  char *operation(int tag);
  private slots:
  void success();
  signals:
  void term();
};

#endif
