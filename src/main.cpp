#include "Scanner.h"

static string path = "../../../Image/160608/laser_off/1.jpeg";

class ImageProcessor : public PointProcessor
{
public:
  void process(Image & image);
};

void ImageProcessor::process(Image & image)
{
  printf("using process !\n");
}

int main(int argc, char **argv)
{
  Scanner scanner;
 // Processor process = new ImageProcessor();
  scanner.create(new ImageProcessor()).run();
//  scanner.create().run();
  return 0;
}
