#ifndef _POINTPROCESSOR_H
#define _POINTPROCESSOR_H

#include "Image.h"

//typedef struct PointProcessor
//{
////  void (*process)(Image & image);
//  virtual void process(Image & image);
//}Processor;

class PointProcessor
{
//  PointProcessor(){}
  public:
    virtual void process(Image & image)=0;
};
#endif
