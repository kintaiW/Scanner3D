#include "Scanner.h"

static string PATH = "../../../Image/160608/laser_off/1.jpeg";
static string FOLDER_PATH = "../../../Image/160608/laser_off/";

class ImageProcessor : public PointProcessor
{
public:
  void process(Image & image);
};

void ImageProcessor::process(Image & image)
{
//  image.show();
  image.addImage(FOLDER_PATH,1);
//  image.addImage(1);
//  printf("main: %s\n",image.getName());
//  printf("image: %p\n",&image);
}

int main(int argc, char **argv)
{
  Scanner scanner;
//  printf("%d",sizeof(void*));
  scanner.create(new ImageProcessor()).addPath(PATH).thread(5).run();
  return 0;
}
