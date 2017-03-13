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

Mat Image::getROI()
{
  Mat img_fg = mat;
  Mat img_bg=imread("../../../Image/160608/background.jpeg");

  Mat img_ROI,img_gray;
  subtract(img_fg, img_bg, img_ROI);
  cvtColor(img_ROI, img_gray, CV_BGR2GRAY);

  threshold(img_gray, img_gray, 0, 255, 8);//8 is OTS

  Mat kernel = getStructuringElement( MORPH_RECT,Size(1,1));
  erode(img_gray, img_gray, kernel);

  vector< vector<Point> > contours, area;
  vector<Vec4i> hierarchy;
  Rect boundRect;

  findContours( img_gray, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

  Mat dst = Mat::zeros(img_gray.size(), CV_8UC3);
  //  sort(contours.begin(), contours.end(),
  //      [](const vector<Point>& c1,const vector<Point>& c2,){
  //      return contourArea(c1, false) > contourArea(c2, false);
  //      });
  sort(contours.begin(), contours.end(), compareContourAreas);
  //  Scalar color(rand()&255, rand()&255, rand()&255);
  Scalar color(255, 255, 255);
  drawContours(dst, contours, 0, color, CV_FILLED, 8, hierarchy);

  boundRect = boundingRect(contours[0]);
  rectangle( dst, boundRect.tl(), boundRect.br(),color,-1,8);

  Mat handC = Mat::zeros(img_gray.size(), CV_8UC3);
  rectangle( handC, Point(1764+50,1164+50),boundRect.br(),color,-1,8);

  //  imwrite("ROI.jpeg",handC);
  bitwise_and(img_fg, dst, dst);
  //  imwrite("ROI.jpg",dst);
  return dst;
}

bool compareContourAreas( vector<Point> contour1, vector<Point> contour2){
  double i = fabs( contourArea(contour1));
  double j = fabs( contourArea(contour2));
  return ( i > j);
}

Image Image::captureLaser()
{
  Mat img_fg = mat;

  bitwise_and(img_fg,getROI(),img_fg);

  Mat imgBGR[3];
  split(img_fg,imgBGR);

  Mat img_G = imgBGR[1];
  Mat mask,ds;
  //CV_THRESH_BINARY | CV_THRESH_OTSU
  threshold(img_G, mask, 0, 255, CV_THRESH_TOZERO | CV_THRESH_OTSU);
  bitwise_and(img_G,mask,ds);
  //Mat ds is result
  threshold(ds,ds,250,255,CV_THRESH_TOZERO);
  return *this;
}

int Image::centerOfMass()
{
 //arg ---(Mat ds,vector<Point2f> & points)
  int h = mat.rows, w = mat.cols;
  Mat_<double> ds = mat;//ds

  for(int y = 0; y < h; y++){
    double sum = 0, sum_pixel = 0;
    int xIndex = 0;
    for(int x = 0; x < w; x++){
      if( ds(y,x) > 0 ){
        sum += ds(y,x) * x;
        sum_pixel += ds(y,x);
      }
    }

    if( sum > 0 && sum_pixel > 0 ){
      xIndex = sum / sum_pixel;
//      points.push_back(Point2i(xIndex, y));
    }
  }
  return 0;
}
