#include <json/json.h>
#include "torrent.h"
#include <QtDebug>

unsigned int Torrent::instanceCount = 0;

Torrent::Torrent() {
  pId = Torrent::instanceCount;
  Torrent::instanceCount++;
  pStatus = 0;
  pName = "";
  pTotalSize = 0;
  pPeersConnected = 0;
  pPeersGettingFromUs = 0;
  pPeersSendingToUs = 0;
  pPercentDone = 0;
};

Torrent::Torrent(Json::Value jsonValue) {
  pId = jsonValue.get("id", "0").asUInt();
  Torrent::instanceCount++;
  pTotalSize = jsonValue.get("totalSize", "0").asDouble();
  pName = jsonValue.get("name", "none").asString().c_str();
  pPeersConnected = jsonValue.get("peersConnected", "0").asUInt();
  pPeersGettingFromUs = jsonValue.get("peersGettingFromUs", "0").asUInt();
  pPeersSendingToUs = jsonValue.get("peersSendingToUs", "0").asUInt();
  pPercentDone = jsonValue.get("percentDone", "0").asDouble();
  pStatus = jsonValue.get("status", "0").asUInt();
};

Torrent::Torrent(const Torrent &t) : QObject(){
  pId = t.pId;
  Torrent::instanceCount++;
  pTotalSize = t.pTotalSize;
  pName = t.pName;
  pPeersConnected = t.pPeersConnected;
  pPeersGettingFromUs = t.pPeersGettingFromUs;
  pPeersSendingToUs = t.pPeersSendingToUs;
  pPercentDone = t.pPercentDone;
  pStatus = t.pStatus;  
};

unsigned int Torrent::id() const {
  return pId;
};

int Torrent::status() const {
  return pStatus;
};

QString Torrent::name() const {
  return pName;
};

unsigned int Torrent::peersConnected() const {
  return pPeersConnected;
};

unsigned int Torrent::peersGettingFromUs() const {
  return pPeersGettingFromUs;
};

unsigned int Torrent::peersSendingToUs() const {
  return pPeersSendingToUs;
};

unsigned long int Torrent::totalSize() const {
  return pTotalSize;
};

float Torrent::percentDone() const {
  return pPercentDone;  
};

bool Torrent::operator==(Torrent other) {
  return id() == other.id();
};

bool Torrent::operator<(Torrent other) {
  return id() < other.id();
};
