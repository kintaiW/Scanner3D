#include "Image.h"

csc::Mutex i_mutex;
/*
 *
 * */
Image::Image(){}
Image::~Image(){}
Image::Image(string & filename)
{
  this->filename = filename;
  this->mat = imread(filename);
//  printf("new c_str %s\n",this->filename.c_str());
//  printf("new       %s\n",filename.c_str());
//  printf("new       %s\n",this->getName());
//  printf("size %d\n",this->getSize());
}

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

static string PATH2 = "../../../Image/160608/laser_off/2.jpeg";
void Image::addImage(int number)
{
  synchronized(i_mutex){
    this->targetRequest = Request(PATH2);
  }
}

static int count_num=1;
void Image::addImage(string folder,int number)
{
  count_num += number;
//  synchronized(i_mutex){
    this->targetRequest = Request((folder.append((to_string(count_num)).c_str())+".jpeg"));
//  }
}

Mat Image::image_new(string& filename)
{
  return this->mat = imread(filename);
}

void Image::show()
{
  namedWindow("w");
  imshow("w",this->mat);
  waitKey(0);
}

