#include "Scanner.h"

/*
 *
 * */
Scanner::Scanner(){}
//Scanner::Scanner(Processor p)
//{
//  this->p = p;
//}

Scanner Scanner::test1(){printf("test1 success!");return *this;}
//Scanner Scanner::test2(){printf("test2 success!");return *this;}
Scanner Scanner::create(void(*func)(Image & image))
{
 // this->p.process = func;
  return *this;
}

Scanner Scanner::create(Processor p)
{
  this->p = p;
//  this->p.process = p.process;
  return *this;
}
//static void create()
//{
//  pthread_t id_1;
//  pthread_t id_2;
//  int i,ret;
//
////  ret=pthread_creat(&id_1,NULL,(void *) ,NULL);
//}

void Scanner::process(Image * image)
{
//printf("using caller success!");
}
/*
 *add image to scanner
 *
 *@param string_list string
 *@return this
 **/
Scanner Scanner::addPath(initializer_list<string> lst)
{
  for(auto beg=lst.begin(); beg!=lst.end(); ++beg)
    addRequest(new Request(*beg));
//  addRequest(new Request("abc"));  
  return *this;
}
/*
 *add path to scheduler 
 *
 *@param request
 * */
void Scanner::addRequest(Request * request)
{
  //if()
  this->scheduler.push(request);
}
/*
 *
 *
 * */
void Scanner::run()
{
  Image image;
  this->p->process(image);
}
/*
 *
 *
 * */
void processRequest(Request * request)
{
//  Image image = this->image.readLocalImage(request);
}
