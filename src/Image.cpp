#include "Image.h"

csc::Mutex i_mutex;
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
  synchronized(i_mutex){
    this->targetRequests.push_back(request);
  }
}

//Mat readLocalImage(){
  
//}

