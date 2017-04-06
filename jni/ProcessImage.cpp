//
// Created by kintai on 17-3-28.
//
#include <cmath>
#include <string>

#include "FutureLog.h"
#include "ProcessImage.h"

ProcessImage::ProcessImage() {
    filePath = "/home/kintai/workspace/scanner/Image/160608/laser_off/";
}
ProcessImage::ProcessImage(std::string folderPath) {
    filePath = folderPath;
}
ProcessImage::~ProcessImage() {}
//process image enter
int
ProcessImage::run(int num) {
//    LOGK("ProcessImage:run %s\n",  getPath(num).c_str());
    LOGK("ProcessImage:run %d\n", num);
    Mat img = imread(getPath(num));
    if ( img.empty() ) return -1;
    std::vector<Point2f> point2D = captureLaser(img);
    int rows = generatePointCloud(num,point2D);
    //LOGK("model rows %d\n", rows);
}
//use to get the number of the image name ,before use nust be set filePath,
std::string
ProcessImage::getPath(int num) {
    std::string path(filePath);
    return path.append((std::to_string(num)).c_str()) + ".jpeg";
}
//the 2D -> 3D,need camera param ,the angle of between laser and camera focus ~
int
ProcessImage::generatePointCloud(int angle, std::vector<Point2f> point2D) {
    //映射关系
    double theta = -(2*angle) * M_PI / 180.0;
    double c = cos(theta), s = sin(theta);
    Mat X,Ry = (Mat_<double>(3,3)<<
                   c, 0, -s,
                   0, 1,  0,
                   s, 0,  c);
    //
    Mat Xwo = Mat(point2D.size(), 3, CV_64FC1, Scalar(0));

  double u, v, du, dv;
  double Xw, Yw, Zw;
  double nume, deno;
  for( int i=0; i < point2D.size(); i++){
    u = point2D[i].x, v = point2D[i].y;
    du= u - cx      , dv= v - cy;

#if 0
    Zw =  (fx*du*l)     / (fx*du+tga);
    Xw =  (fx*du*l)*tga / (fx*du+tga);
    Yw = -(fy*du*l)*tga / (fx*du+tga);
#else
    nume = fx*du*l, deno = fx*du+tga;
    Zw = nume     / deno;
    Xw = nume*tga / deno;
    nume = -fy*dv*l;
    Yw = nume*tga / deno;
#endif

    X = (Mat_<double>(1,3)<<Xw, Yw, Zw);
    Xwo.row(i)= (Ry * X.t()).t();
  }
  model.push_back(Xwo);
  return Xwo.rows;
}

int
ProcessImage::generatePointCloud(int angle, std::vector<Point2f> point2D, std::vector<Mat>& model) {
    //映射关系
    double theta = -(2*angle) * M_PI / 180.0;
    double c = cos(theta), s = sin(theta);
    Mat X,Ry = (Mat_<double>(3,3)<<
                   c, 0, -s,
                   0, 1,  0,
                   s, 0,  c);
    //
    Mat Xwo = Mat(point2D.size(), 3, CV_64FC1, Scalar(0));

  double u, v, du, dv;
  double Xw, Yw, Zw;
  double nume, deno;
  for( int i=0; i < point2D.size(); i++){
    u = point2D[i].x, v = point2D[i].y;
    du= u - cx      , dv= v - cy;

#if 0
    Zw =  (fx*du*l)     / (fx*du+tga);
    Xw =  (fx*du*l)*tga / (fx*du+tga);
    Yw = -(fy*du*l)*tga / (fx*du+tga);
#else
    nume = fx*du*l, deno = fx*du+tga;
    Zw = nume     / deno;
    Xw = nume*tga / deno;
    nume = -fy*dv*l;
    Yw = nume*tga / deno;
#endif

    X = (Mat_<double>(1,3)<<Xw, Yw, Zw);
    Xwo.row(i)= (Ry * X.t()).t();
  }
  model.push_back(Xwo);
  return Xwo.rows;
}

// the center of mass calculate
static int
centerOfMass(Mat image, std::vector<Point2i>& centers) {
  int h = image.rows, w = image.cols;
  Mat_<double> ds = image;

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
      centers.push_back(Point2i(xIndex, y));
    }
  }
  if (centers.size() == 0) return -1;
  return 0;
}

int
ProcessImage::captureLaser(Mat image, std::vector<Point2i>& points) {
    if ( image.empty() ) return -1;

    Mat imgBGR[3];
    split(image,imgBGR);

    Mat imgSingleChannel = imgBGR[GREEN];
    Mat mask, dst;

    threshold(imgSingleChannel, mask, 0, 255, CV_THRESH_TOZERO | CV_THRESH_OTSU);
    bitwise_and(imgSingleChannel, mask, dst);
    threshold(imgSingleChannel, dst, 250, 255, CV_THRESH_TOZERO);

    return centerOfMass(dst, points);
}

static std::vector<Point2f>
centerOfMass(Mat image) {
  int h = image.rows, w = image.cols;
  Mat_<double> ds = image;
  std::vector<Point2f> centers;

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
      centers.push_back(Point2f(xIndex, y));
    }
  }
  return centers;
}
//get the center of laser in the image
std::vector<Point2f>
ProcessImage::captureLaser(Mat image) {
//    if ( image.empty() ) return -1;

    Mat imgBGR[3];
    split(image,imgBGR);

    Mat imgSingleChannel = imgBGR[GREEN];
    Mat mask, dst;

    threshold(imgSingleChannel, mask, 0, 255, CV_THRESH_TOZERO | CV_THRESH_OTSU);
    bitwise_and(imgSingleChannel, mask, dst);
    threshold(imgSingleChannel, dst, 250, 255, CV_THRESH_TOZERO);

    return centerOfMass(dst);
}

// check whether opencv and jni is support
int
readLocalImage(std::string& path) {
    Mat img = imread(path);
    return 6;
}
