#include "Request.h"

Request::Request(){}
Request::~Request(){}
Request::Request(string file)
{
  this->file = file; 
  this->isValid = true;
}

Request::Request(string file,int id)
{
  this->id = id;
  this->file = file; 
  this->isValid = true;
}

string Request::request2String(Request * request)
{
  return this->file;
}

