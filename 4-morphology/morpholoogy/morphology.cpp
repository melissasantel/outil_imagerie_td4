#include <morphology.hpp>

using namespace cv;

void
mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar*))
{
  Size size_se = se.size();
  Size size_ims = ims.size();
  int radius = (size_se.width-1)/2;
  uchar max_min;
  for ( int i = 0; i < size_ims.height; i++ ){
    for ( int j = 0; j < size_ims.width; j++ ){
      max_min = ims.ptr<uchar>(i)[j];
      for ( int u = -radius; u <= radius; u++ ){
        for ( int v = -radius; v <= radius; v++){
          // if ( (i+u < 0) || (i+u > size_ims.height) || (j+v < 0) || (j+v > size_ims.width) ) //seg fault
          //   continue;
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
  if ( val > *max ){
    *max = val;
  }
}

void
minimum(uchar val, uchar* min)
{
  if ( val < *min ){
    *min = val;
  }
}
