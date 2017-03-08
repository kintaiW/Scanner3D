#include "Request.h"

Request::Request(){}
Request::~Request(){}
Request::Request(string file)
{
  this->file = file; 
}

string Request::request2String(Request * request)
{
  return this->file;
}

