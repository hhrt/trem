#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QtCore>

class TRPCSessionException : public QtConcurrent::Exception {
  private:
  chat *msg;
  public:
  TRPCSessionException() {};
  TRPCSessionException(char *m) { strcpy(msg, m); }
  void raise() const { throw *this; }
  Exception *clone() const { return new TRPCSessionException(*this); }
  char message() { return msg; }
  protected:
  setMsg(char *m) { strcpy(msg,m); }
};

//class DataRecievingErrorException : public TRPCSessionException {


