#include <morphology.hpp>

using namespace cv;

void
mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar*))
{
  Size size_se = se.size();
  Size size_ims = ims.size();
  int radius = (se.width-1)/2;
  uchar max;
  int center_shape_value;

  for ( int i = 0; i < size_ims.height; i++ ){
    for ( int j = 0; j < size_ims.width; j++ ){
      center_shape_value = ims.at(i,j);
      max_min = center_shape_value;
      for ( int m = -radius; m <= radius; m++ ){
        for ( int n = -radius; n <= radius; n++){
          if ( ((i+m < 0) || (i+m > size_ims.height)) || ((j+n < 0) || (j+n > size_ims.width)) ) //seg fault
            continue;
          if ( ims.ptr<uchar>(m)[n] == 255 ){
            pf(ims.ptr<uchar>(i+m)[j+n], &max);
          }
          // uchar* i_line_pointer = ims.ptr<uchar>(i+m);
          // current ims pixel is i_line_pointer[j+n]
        }
      }
    }
  }
}

void
maximum(uchar val, uchar* max)
{
  if ( val > *max )
    *max = val;
}

void
minimum(uchar val, uchar* min)
{
  if ( val < *min )
    *min = val;
}
