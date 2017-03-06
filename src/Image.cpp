#include "Image.h"
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
void Image::addImage(Request * request)
{
  this->iq.paths.push(*request);
}

Mat readLocalImage(){
  
}

