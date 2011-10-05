#ifndef TRPCSESSION_H
#define TRPCSESSION_H

#include <QObject>
#include <QHttp>
#include <QStringList>
#include "torrent.h"
#include "defines.h"

class QBuffer;
class QString;

class TRPCSession : public QObject {
  Q_OBJECT
  
  public:
  TRPCSession();
  TRPCSession(QString h, QString p, QString u);
  void init(); //to make private
  void setHost(QString h);
  void setPort(QString p);
  void setUrl(QString u);
  void setIds(QList<unsigned int> &ids);
  void setTag(TRPCTag tag);//to make private, or remove
  QStringList fields() const;
  QString result() const;
  int torrentsCount() const;
  Torrent torrent(unsigned int id);
  void getTorrentsList(QList<unsigned int> *ids = NULL);
  void stopTorrents(QList<unsigned int> *ids = NULL);
  void startTorrents(QList<unsigned int> *ids = NULL);
  void doit();//to make private

  private:
  QList<Torrent *> torrents;
  QList<unsigned int> *pIds;
  QString host;
  QString port;
  QString url;
  qint16 pTag;
  QString pResult;
  QStringList pFields;
  QString tSessionId;
//system objects
  QHttp *http;
  QBuffer *response;
  QByteArray request;
  QHttpRequestHeader requestHeader;
  QBuffer *requestBody;
//system methods
  void parseResponseData();
  QString generateJsonRequest();

  private slots:
  void dataReceived(bool error);

  signals:
  void err(int errorCode);
  void success();

};


#endif
