#include "Image.h"

csc::Mutex mutex;
/*
 *
 * */
Image::Image(){}
Image::~Image(){}

/*
 *add image path to ImageQueue 
 *
 *@param 
 * */
void Image::addImage(Request request)
{
  synchronized(mutex){
    this->targetRequests.push_back(request);
  }
}

//Mat readLocalImage(){
  
//}

