#include <QObject>
#include <QDebug>
#include <iostream>
#include "app.h"
#include "reciever.h"
#include "defines.h"
#include "exceptions.h"
#include <QStringList>

int main(int argc, char **argv) {
  App app(argc, argv, QApplication::Tty);
  const QString usage = QObject::tr("Usage: ")+app.arguments().at(0)+QObject::tr("[list|stop|start] [id1,id2,...,idN]\n");
  Reciever reciever("localhost");
  QList<unsigned int> *ids = NULL;
  int cmd = 0;
  QObject::connect(&reciever, SIGNAL(term()), &app, SLOT(quit()));
  //Dealing with the command line arguments
  if(app.arguments().count() > 1) {
    if(app.arguments().at(1) == QString("list"))  cmd = GetTorrentsList;
    if(app.arguments().at(1) == QString("start")) cmd = StartTorrents;
    if(app.arguments().at(1) == QString("stop"))  cmd = StopTorrents;
    if(app.arguments().count() > 2) {
      ids = new QList<unsigned int>;
      QStringList strIds = app.arguments().at(2).split(",");
      int id;
      int i;
      for(i=0;i<strIds.count();i++) {
        bool ok = false;
        id = strIds.at(i).toInt(&ok, 10);
        if(ok) ids->push_back(id);
      }
    }
/*    if(((cmd == StopTorrents)||(cmd == StartTorrents))&&(ids == NULL)) {
      std::cerr << "Error! Torrents ids must be specified in format: id1,id2,...,idN\n";
      return -1;
    }*/
  }
  if(cmd == 0) {
    std::cerr << "Wrong arguments.\n";
    std::cout << usage.toAscii().data();
    return -1;
  }
  //-----
  try {
  reciever.run(cmd, ids);
  }
  catch(TRPCSessionException &e) {
    qDebug() << "Exception raised:" << e.message();
    return -1;
  };
  return app.exec();
};
