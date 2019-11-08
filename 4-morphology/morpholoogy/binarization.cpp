#include <iostream>
#include <cstdlib>
#include "erosion.cpp"

using namespace cv;
using namespace std;

void
process(int thmin, int thmax, const char* imsname, const char* imdname)
{
  (void)thmin;
  (void)thmax;

  // process("disk-10.png", imsname, "gear_erosion.png");
  // Mat ims_full(imread(imsname, 0));
  // Mat ims_diff(ims_full - ims_erosion);
  Mat ims = imread(imsname, 0);
  Mat imd (ims.size(),CV_8UC1);

  for (int i=0; i<ims.rows; i++ ){
    for( int j=0; j<ims.cols; j++){
      if( ims.ptr<uchar>(i)[j] < thmin){
        imd.ptr<uchar>(i)[j] =0;
      }
      else if( ims.ptr<uchar>(i)[j] < thmax && ims.ptr<uchar>(i)[j] >= thmax){
        imd.ptr<uchar>(i)[j] =255;
      }
    }
  }
  // namedWindow("gear_res", WINDOW_AUTOSIZE);
  // imshow("gear_res", ims_diff);
  // waitKey(0);

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
