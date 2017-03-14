#ifndef _REQUEST_H
#define _REQUEST_H

#include <string>

using namespace std;

class Request 
{
public:
  Request();
  Request(string file);
  Request(string file,int id);
  ~Request();

  string file;
  int id;
  bool isValid = false; 
  inline string getPath(){return this->file;}
  string request2String(Request * request);
private:
};
#endif
