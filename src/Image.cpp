#include "Image.h"
/*
 *
 * */
Image::Image(){}
Image::~Image(){}
Image::Image(string & filename)
{
  this->filename = filename;
  this->mat = imread(filename);
}

Image::Image(Request & request)
{
  filename = request.file;
  mat = imread(filename);
}
/*
 *add image path to ImageQueue 
 *
 *@param 
 * */
void Image::addImage(Request request)
{
    this->targetRequests.push_back(request);
}

static string PATH2 = "../../../Image/160608/laser_off/2.jpeg";
void Image::addImage(int number)
{
    this->targetRequest = Request(PATH2);
}

static int count_num=1;
void Image::addImage(string folder,int number)
{
  count_num += number;
  targetRequest = Request((folder.append((to_string(count_num)).c_str())+".jpeg"));
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

