#include <morphology.hpp>

using namespace cv;

void
mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar*))
{
  //-- Creates variables we need
  Size size_se = se.size();
  Size size_ims = ims.size();
  int radius = (size_se.width-1)/2;
  uchar max_min;
  //-- Browse the image
  for ( int i = 0; i < size_ims.height; i++ ){
    for ( int j = 0; j < size_ims.width; j++ ){
      //-- Initialise the max/min value
      max_min = ims.ptr<uchar>(i)[j];
      //-- Browse the structurant element to find max/min
      for ( int u = -radius; u <= radius; u++ ){
        for ( int v = -radius; v <= radius; v++){
          if(i+u>=0 && j+v>=0 && i+u<size_ims.height && j+v<size_ims.width){
            if (se.ptr<uchar>(u+radius)[v+radius] == 255 ){
              pf(ims.ptr<uchar>(i+u)[j+v], &max_min);
            }
          }
        }
      }
      imd.ptr<uchar>(i)[j] = max_min;
    }
  }
}

void
maximum(uchar val, uchar* max)
{
  //-- Get the maximum value
  if ( val > *max ){
    *max = val;
  }
}

void
minimum(uchar val, uchar* min)
{
  //-- Get the minnimum value
  if ( val < *min ){
    *min = val;
  }
}
