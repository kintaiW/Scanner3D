#include "Scanner.h"
#include <fstream>

// image foler path
static string FOLDER_PATH = "../res/laser/";
// camera param
static double camera_param[6] = {
  3469.6151335,
  3449.2845482,
  1944.3733099,
  1571.7636110,
  0.454545    ,
  330.0       ,
};
//ply model head
string getPlyHeader(int num)
{
  stringstream total;
  total << num;
  string PLY_HEAD("ply\n");
  PLY_HEAD += "format ascii 1.0\n";
  PLY_HEAD += "element vertex " + total.str() + "\n";
  PLY_HEAD += "property float x\n";
  PLY_HEAD += "property float y\n";
  PLY_HEAD += "property float z\n";
  PLY_HEAD += "property uchar red\n";
  PLY_HEAD += "property uchar green\n";
  PLY_HEAD += "property uchar blue\n";
  PLY_HEAD += "end_header\n";
  return PLY_HEAD;
}

static long basesec = 0;
long getTimeMs(){
  struct timeval tv;
  long nowtime;
  gettimeofday(&tv, 0);
  if( basesec == 0){
    basesec = tv.tv_sec;
  }
  nowtime = (int64_t)(tv.tv_sec - basesec) * (int64_t)1000 +
    (int64_t)tv.tv_usec/1E3;
  return nowtime;
}

class ImageProcessor : public PointProcessor
{
public:
  vector<Mat> colors,model;
  void process(Image & image);
  void getModel();
};

void ImageProcessor::getModel()
{
  int points = 0;
  Mat_<double> p,c;
  ofstream ofile,oTemp;
  ofile.open("model.ply",ios::ate | ios::trunc);
  oTemp.open("temp",ios::app);

  for(vector<Mat>::iterator mc=colors.begin(),mp=model.begin(); mc!=colors.end(); mc++,mp++){
    points += (*mp).rows;
    p = *mp, c = *mc;
    for(int i=0; i<(*mc).rows; i++){
      oTemp<<p(i,0)<<" "<<p(i,1)<<" "<<p(i,2)<<" "
           <<c(i,0)<<" "<<c(i,1)<<" "<<c(i,2)<<"\n";
    }
  }
  oTemp.close();
  ifstream is("temp");
  string line;

  ofile<<getPlyHeader(points);
  while ( getline(is,line) )
    ofile<<line<<"\n";

  is.close();
  ofile.close();
  system("rm temp");
}

void ImageProcessor::process(Image & image)
{
  long time_start=getTimeMs();
  image.captureLaser();
  image.addColor(colors);
  image.generatePointCloud(camera_param, model);
  printf("\ntook: %lld ", getTimeMs()-time_start);
}

int main(int argc, char **argv)
{
  long time_start=getTimeMs();
  Scanner scanner;
  ImageProcessor * ip = new ImageProcessor();
  scanner.create(ip).addLocalPath(FOLDER_PATH).thread(16).run();
  ip->getModel();
  printf("\ntotal took: %lld\n", getTimeMs()-time_start);
  return 0;
}
