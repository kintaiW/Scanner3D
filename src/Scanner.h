#ifndef _SCANNER_H
#define _SCANNER_H

#include <initializer_list>
#include <string>
#include <pthread.h>

#include "Image.h"
#include "Request.h"
#include "Scheduler.h"
#include "PointProcessor.h"

using namespace std;

typedef PointProcessor * Processor;

class Scanner
{
protected:
  Image image;
  Scheduler scheduler;
public:
  Scanner();
//  Scanner(Processor p);
//  ~Scanner();

  Scanner test1();
  //Scanner test2();
  Scanner create(void (*func) (Image&));
  Scanner create(Processor p);

  void bind();
  void run();
  void process(Image *image);
  void processRequest(Request * request);
  Scanner addPath(initializer_list<string> lst);
private:
  Processor p;
  void addRequest(Request * request);
};

#endif
