#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QtCore>
#include <QString>

//TRPCSession exceptionn begins

class TRPCSessionException : public QtConcurrent::Exception {
  private:
  QString msg;
  public:
  TRPCSessionException() { msg = "TRPCSessionException"; }
  ~TRPCSessionException() throw() {};
  void raise() const { throw *this; }
  Exception *clone() const { return new TRPCSessionException(*this); }
  QString message() { return msg; }
  protected:
  void setMsg(QString m) { msg = m; }
};

class WrongTorrentIdException : public TRPCSessionException {
  public:
  WrongTorrentIdException() : TRPCSessionException() {
    setMsg("Wrong torrent ID.");
  }
};

class MemoryAccessErrorException : public TRPCSessionException {
  public:
  MemoryAccessErrorException() : TRPCSessionException() {
    setMsg("Wrong torrent ID.");
  }
};

class WrongTagException : public TRPCSessionException {
  public:
  WrongTagException() : TRPCSessionException() {
    setMsg("Wrong tag.");
  }
};

class JsonParsingErrorException : public TRPCSessionException {
  public:
  JsonParsingErrorException() : TRPCSessionException() {
    setMsg("JSON parsing error.");
  }
};

class MissingTorrentsBlockException : public TRPCSessionException {
  public:
  MissingTorrentsBlockException() : TRPCSessionException() {
    setMsg("Missing torrents block.");
  }
};

class DataRecievingErrorException : public TRPCSessionException {
  public:
  DataRecievingErrorException() : TRPCSessionException() {
    setMsg("Data recieving error.");
  }
};

class MissingIdsListException : public TRPCSessionException {
  public:
  MissingIdsListException() : TRPCSessionException() {
    setMsg("Missing ids list.");
  }
};

class WrongHttpAnswerException : public TRPCSessionException {
  public:
  WrongHttpAnswerException() : TRPCSessionException() {
    setMsg("Wrong http answer status.");
  }
};

//TRPCSession exceptionn ends

#endif
