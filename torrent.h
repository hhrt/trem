#ifndef TORRENT_H
#define TORRENT_H

#include <QtGlobal>
#include <QObject>
#include "json/json.h"
#include "defines.h"

class Torrent : public QObject {
  Q_OBJECT

  public:
  Torrent();
  Torrent(Json::Value jsonValue);
  Torrent(const Torrent &t);
  unsigned int id() const;
  int status() const;
  QString name() const;
  unsigned int peersConnected() const;
  unsigned int peersGettingFromUs() const;
  unsigned int peersSendingToUs() const;
  unsigned long int totalSize() const;
  float percentDone() const;

  bool operator==(Torrent other);
  bool operator<(Torrent other);

  private:
  static unsigned int instanceCount;
  unsigned int pId;
  int pStatus;
  QString pName;
  unsigned int pPeersConnected;
  unsigned int pPeersGettingFromUs;
  unsigned int pPeersSendingToUs;
  unsigned long int pTotalSize;
  float pPercentDone;

};

#endif
