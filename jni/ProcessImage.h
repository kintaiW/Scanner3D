//
// Created by kintai on 17-3-28.
//

#ifndef OPENCAMERA_CODE_PROCESSIMAGE_H
#define OPENCAMERA_CODE_PROCESSIMAGE_H

#include <vector>
#include <string>
#include <atomic>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

//using namespace std;
using namespace cv;

class ProcessImage
{
public:
    ProcessImage();
//    ~ProcessImage();
    int run(int num);
    int captureLaser(Mat image, std::vector<Point2i>& centerPoints);
    std::vector<Point2f> captureLaser(Mat image);//std::move();
    int generatePointCloud(int angle, std::vector<Point2f> point2D);
    int generatePointCloud(int angle, std::vector<Point2f> point2D, std::vector<Mat>& model);
    std::string getPath(int num);
//    int setPath();
private:
    std::string filePath;
//    std::vector<Point2f> point2D;
    std::vector< Mat > colors;//many thread write here,so maybe try atomic
    std::vector< Mat > model;
};

static double cameraParam[6] = {
  3469.6151335,
  3449.2845482,
  1944.3733099,
  1571.7636110,
  0.454545    ,
  330.0       ,
};
//camera param
#define fx 1/cameraParam[0]
#define fy 1/cameraParam[1]
#define cx cameraParam[2]
#define cy cameraParam[3]
#define tga cameraParam[4]
#define l  cameraParam[5]

enum {
    BLUE  = 0,
    GREEN = 1,
    RED   = 2,
};

int readLocalImage(std::string& path);


#endif //OPENCAMERA_CODE_PROCESSIMAGE_H
