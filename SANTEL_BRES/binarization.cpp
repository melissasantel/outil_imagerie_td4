#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(int thmin, int thmax, const char* imsname, const char* imdname)
{
  //-- Declare variables
  //-- And read the image given in value
  Mat ims = imread(imsname, 0);
  Size ims_s = ims.size();
  Mat imd (ims.size(),CV_8UC1);
  //-- Browse the image to make the binarization
  for (int i=0; i<ims_s.height; i++ ){
    for( int j=0; j<ims_s.width; j++){
      if(ims.ptr<uchar>(i)[j] > thmin && ims.ptr<uchar>(i)[j] <= thmax){
        imd.ptr<uchar>(i)[j] = 255;
      }
      else{
        imd.ptr<uchar>(i)[j] = 0;
      }
    }
  }
  //-- Save the binarized image
  imwrite(imdname, imd);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" thmin thmax ims imd"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  int thmin = atoi(argv[1]);
  int thmax = atoi(argv[2]);
  process(thmin, thmax, argv[3], argv[4]);
  return EXIT_SUCCESS;
}
