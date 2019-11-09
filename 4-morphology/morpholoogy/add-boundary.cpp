#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imboundary, const char* imsname, const char* imdname)
{
  Mat ims = imread(imsname, 1);
  Mat im_boundary = imread(imboundary, 0);
  Size imb = im_boundary.size();
  Mat imd = ims.clone();

  for (int i=0; i<imb.height; i++ ){
    for( int j=0; j<imb.width; j++){
      if( im_boundary.ptr<uchar>(i)[j] != 0){
        imd.ptr<Vec3b>(i)[j] = Vec3b(0,0,255);
      }
    }
  }

  imwrite(imdname, imd);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" thmin thmax ims imd"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2], argv[3]);
  return EXIT_SUCCESS;
}
