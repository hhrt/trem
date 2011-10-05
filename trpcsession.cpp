#include <QHttp>
#include <QtDebug>
#include <QBuffer>
#include <QString>
#include <QTextStream>

#include "trpcsession.h"
#include "exceptions.h"

TRPCSession::TRPCSession() {
  host = "127.0.0.1";
  port = "9091";
  url = "/transmission/rpc/";
  init();
};

TRPCSession::TRPCSession(QString h, QString p, QString u) {
  host = h;
  port = p;
  url = u;
  init();
};

void TRPCSession::init() {
  pIds = NULL;
  torrents.clear();
  http = new QHttp();
  connect(http, SIGNAL(done(bool)), this, SLOT(dataReceived(bool)));
  response = new QBuffer();
  requestBody = new QBuffer();
  tSessionId = "";
  request.clear();
  http->setHost(host, port.toInt());

  pFields.append("id");
  pFields.append("name");
  pFields.append("totalSize");
  pFields.append("peers");
  pFields.append("peersConnected");
  pFields.append("peersGettingFromUs");
  pFields.append("peersSendingToUs");
  pFields.append("percentDone");
  pFields.append("status");
};

void TRPCSession::setHost(QString h) {
  host = h;
  http->setHost(host, port.toInt());
};

void TRPCSession::setPort(QString p) {
  port = p;
  http->setHost(host, port.toInt());
};

void TRPCSession::setUrl(QString u) {
  url = u;
};

QStringList TRPCSession::fields() const {
  return pFields;
};

QString TRPCSession::result() const {
  return pResult;
};

int TRPCSession::torrentsCount() const {
  return torrents.count();
};

Torrent TRPCSession::torrent(unsigned int id) {
  if(id > torrents.count()) {
    qDebug() << "id > count";
    throw *(new WrongTorrentIdException);
  }
  if(torrents.at(id)==NULL) {
    qDebug() << "torrent: access error";
    throw 44;
  }
  Torrent torr(*torrents.at(id));
  return torr;
};

QString TRPCSession::generateJsonRequest() {
  QString output;
  QTextStream out(&output, QIODevice::ReadWrite);
  unsigned int i;
  unsigned int j;
  QString method;

  switch(pTag) {
    case GetTorrentsList:
    method = "torrent-get";
    break;
    case StopTorrents:
    method = "torrent-stop";
    break;
    case StartTorrents:
    method = "torrent-start";
    break;
    default:
    throw 3;//make it !!!
  }

  out << "{ \"arguments\" : { ";
  if((pIds) && (pIds->count()>0)) {
    out << "\"ids\" : [ ";
    for(j=0;j<pIds->count()-1;j++)
      out << QString::number(pIds->at(j)) << ", ";
    out << QString::number(pIds->at(j)) <<" ] ";
  }
  if(pTag == GetTorrentsList) {
    if((pIds) && (pIds->count()>0))
      out << ", ";
    out << "\"fields\" : [ ";
    for(i=0; i<pFields.count()-1;i++)
      out << "\"" << pFields[i] << "\", ";
    out << "\"" << pFields[i] << "\" ]";
  }
  out << " }, ";
  out << "\"method\" : \"" << method << "\", ";
  out << "\"tag\" : " << QString::number(pTag);
  out << " } ";

  return output;

};

void TRPCSession::parseResponseData() {
  Json::Reader reader;
  Json::Value root;
  Json::Value torrentsValue;
  if(!reader.parse(response->buffer().data(), root)) 
    throw 1; //don't forget to make my own exception classes

  pResult = root.get("result", "none").asString().c_str();
  pTag = root.get("tag", "0").asUInt();

  if(pTag == GetTorrentsList) {
    torrentsValue = root["arguments"]["torrents"];
    if(torrentsValue.isNull())
      throw 22; //and one more time: don't you, fucking, forget!!!
    Torrent *torrent;
    torrents.clear();
    unsigned int i;
    for(i=0;i<torrentsValue.size();i++) {
      torrent = new Torrent(torrentsValue[i]);
      torrents.push_back(torrent);
    }
  }
};

void TRPCSession::doit() {
  if(response->isOpen()) {
    response->buffer().clear();
    response->close();
  }
  if(requestBody->isOpen()) {
    requestBody->buffer().clear();
    requestBody->close();
  }
  requestBody->setData(generateJsonRequest().toAscii());
  requestHeader.setRequest("POST", url);
  requestHeader.setValue(host, port);
  requestHeader.setValue("X-Transmission-Session-Id", tSessionId);
  http->request(requestHeader, requestBody->data(), response); //make return value check
};

void TRPCSession::dataReceived(bool error){
  if(error)
    throw *(new DataRecievingErrorException); //don't forget to make my own exceptions
  else {
    switch(http->lastResponse().statusCode()) {
      case 409:
      tSessionId = http->lastResponse().value("X-Transmission-Session-Id");
      getTorrentsList();
      break;
      case 200:
      parseResponseData();
      emit success();
      break;
      default:
      emit err(10);//some error, I must think about this
    }
  }
};

void TRPCSession::setIds(QList<unsigned int> &ids) {
  if(!pIds)
    pIds = new QList<unsigned int>;
  else {
    delete pIds;
    pIds = new QList<unsigned int>(ids);
  }
};

void TRPCSession::setTag(TRPCTag tag) {
  pTag = tag;
};

void TRPCSession::getTorrentsList(QList<unsigned int> *ids) {
  pTag = GetTorrentsList;
  if(ids) {
    if(pIds) delete pIds;
    pIds = new QList<unsigned int>(*ids);
  }    
  else delete pIds;
  doit();
};

void TRPCSession::stopTorrents(QList<unsigned int> *ids) {
  pTag = StopTorrents;
  if(ids) {
    if(pIds) delete pIds;
    pIds = new QList<unsigned int>(*ids);
  }
  if(!pIds)
    throw 3;
  doit();
};

void TRPCSession::startTorrents(QList<unsigned int> *ids) {
  pTag = StartTorrents;
  if(ids) {
    if(pIds) delete pIds;
    pIds = new QList<unsigned int>(*ids);
  }
  if(!pIds)
    throw 3;
  doit();
};

