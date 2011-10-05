#include "reciever.h"
#include "trpcsession.h"
#include "torrent.h"
#include "iostream"

Reciever::Reciever(const char *host, const char *port, const char *url) {
  session = new TRPCSession();
  connect(session, SIGNAL(success()), this, SLOT(success()));
  session->setHost(host);
  session->setPort(port);
  session->setUrl(url);
};

void Reciever::run() {
  session->getTorrentsList();
};

void Reciever::success() {
  std::cout << "result: \'" << session->result().toAscii().data() << "\'\n";
  std::cout << "torrents count: \'" << session->torrentsCount() << "\'\n";
  int i;
  std::cout << "Torrents:\n";
  for(i=0;i<session->torrentsCount();i++) {
    std::cout << "[id:] \'" << session->torrent(i).id() <<"\' [name:] \'" <<  session->torrent(i).name().toAscii().data() 
              << "\' [done:] " << session->torrent(i).percentDone() <<"% \n";
  }

  emit term();
};

