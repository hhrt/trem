#include "reciever.h"
#include "trpcsession.h"
#include "torrent.h"
#include "iostream"
#include "defines.h"
#include "exceptions.h"
#include <QDebug>

Reciever::Reciever(const char *host, const char *port, const char *url) {
  session = new TRPCSession();
  connect(session, SIGNAL(success()), this, SLOT(success()));
  session->setHost(host);
  session->setPort(port);
  session->setUrl(url);
};

Reciever::~Reciever() {
  delete session;
};

void Reciever::run(int actionCode, QList<unsigned int> *ids) {
  switch(actionCode) {
    case GetTorrentsList:
    //qDebug() << "GetTorrentsList";
      session->getTorrentsList(ids);
    break;
    case StopTorrents:
    //qDebug() << "StopTorrents";
      if((ids == NULL) || (ids->count() == 0))
        throw *(new MissingIdsListException);
      else
        session->stopTorrents(ids);
    break;
    case StartTorrents:
    //qDebug() << "StartTorrents";
      if((ids == NULL) || (ids->count() == 0))
        throw *(new MissingIdsListException);
      else
        session->startTorrents(ids);
    break;
    default:
      throw *(new WrongTagException);
  }
};

void Reciever::success() {
  std::cout << "result: \'" << session->result().toAscii().data() << "\'\n";
//  std::cout << "tag: \'" << session->tag() << "\'\n";
  switch(session->tag()) {
    case GetTorrentsList:
    std::cout << "torrents count: \'" << session->torrentsCount() << "\'\n";
    int i;
    std::cout << "Torrents:\n";
    for(i=0;i<session->torrentsCount();i++) {
      std::cout << "[id:] \'" << session->torrent(i).id() <<"\' [name:] \'" <<  session->torrent(i).name().toAscii().data()                << "\' [done:] " << session->torrent(i).percentDone() <<"% ";
      if(session->torrent(i).status() == (1 << 4))
        std::cout << "paused";
      else
        std::cout << "runned";
      std::cout << "\n";
    }
    break;
    case StopTorrents:
    break;
    case StartTorrents:
    break;
    defaults:
    std::cout << "Unknown tag.\n";
  }
  emit term();
};

