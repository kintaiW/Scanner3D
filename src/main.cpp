#include "Scanner.h"

static string PATH = "../../../Image/160608/laser_off/1.jpeg";

class ImageProcessor : public PointProcessor
{
public:
  void process(Image & image);
};

void ImageProcessor::process(Image & image)
{
  
  printf("using process %s\n",&image);
}

int main(int argc, char **argv)
{
  Scanner scanner;
  scanner.create(new ImageProcessor()).addPath(PATH).thread(5).run();
  return 0;
}
