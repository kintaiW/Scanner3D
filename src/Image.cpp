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
  id = request.id;
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

static string PATH2 = "../res/laser/2.jpeg";
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
  Mat img_bg=imread("../res/background.jpeg");

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
#if 1  
    sort(contours.begin(), contours.end(),
        [](const vector<Point>& c1,const vector<Point>& c2){
        return contourArea(c1, false) > contourArea(c2, false);
        });
#else
  sort(contours.begin(), contours.end(), compareContourAreas);
#endif
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

Mat Image::getLocalROI()
{
  return imread("../res/ROI.jpeg");
}

Image Image::captureLaser()
{
  Mat img_fg = mat;

  bitwise_and(img_fg,getLocalROI(),img_fg);

  Mat imgBGR[3];
  split(img_fg,imgBGR);

  Mat img_G = imgBGR[1];
  Mat mask,ds;
  //CV_THRESH_BINARY | CV_THRESH_OTSU
  threshold(img_G, mask, 0, 255, CV_THRESH_TOZERO | CV_THRESH_OTSU);
  bitwise_and(img_G,mask,ds);
  //Mat ds is result
  threshold(ds,ds,250,255,CV_THRESH_TOZERO);

  if ( centerOfMass(ds,point2D) == -1)
    printf("could not find any point in image\n");
//  printf("captureLaser %d\n",point2D.size());
  return *this;
}

int Image::centerOfMass(Mat mat,vector<Point2f> & point)
{
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
      point.push_back(Point2i(xIndex, y));
    }
  }
  if (point.size() == 0) return -1;
  return 0;
}

Mat Image::addColor(vector<Mat>& colors)
{
  color = Mat(point2D.size(),3,CV_64FC1,Scalar(0));
  double u,v;
  Mat x = (Mat_<double>(1,3)<<0,0,0);
  int r = rand()&255, g = rand()&255, b =rand()&255;
  for(int i=0; i<point2D.size(); i++){
    u = point2D[i].x, v = point2D[i].y;
#if 0    
    x = (Mat_<double>(1,3)<<
         (int)mat.at<Vec3b>(v,u)[0],
         (int)mat.at<Vec3b>(v,u)[1],
         (int)mat.at<Vec3b>(v,u)[2]);
#else
    x = (Mat_<double>(1,3)<<r, g, b);
#endif    
    x.copyTo(color.row(i));
  }
  colors.push_back(color);
  return color;
}

#define PI 3.14159265
Mat Image::generatePointCloud(double * CamParam, vector<Mat>& model)
{
  Xwo = Mat(point2D.size(),3,CV_64FC1,Scalar(0));
  double fx = 1/CamParam[0];
  double fy = 1/CamParam[1];
  double cx = CamParam[2];
  double cy = CamParam[3];
  double tga= CamParam[4];
  double l  = CamParam[5];

  double theta = -(2*getID()) * PI / 180.0;

  double c = cos(theta), s = sin(theta);

  Mat X,Ry = (Mat_<double>(3,3)<<
               c, 0, -s,
               0, 1,  0,
               s, 0,  c);

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
  return Xwo;
}
