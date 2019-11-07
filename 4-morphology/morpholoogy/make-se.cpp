#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};

void
process(const int shape, const int halfsize, const char* imdname)
{
  cout<< "\n############### exercice : make-se  ###############\n"<<endl;
  //Create variables
  int mat_size = 2 * halfsize + 1;
  Mat imd = Mat::zeros( mat_size, mat_size, CV_8UC1);
  int center_ij = halfsize;
  int x1, x2;
  double norme_x;
  // Create the structurant element the type of the variable shape
  if( shape == SQUARE ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
            x1 = abs( i - center_ij );
            x2 = abs( j - center_ij );
            if ( x1 >= x2 )
              norme_x = x1;
            else
              norme_x = x2;
            if ( norme_x <= halfsize )
              imd.ptr<uchar>(i)[j] = 255;
      }
    }
  }
  else if ( shape == DIAMOND ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        x1 = abs( i - center_ij );
        x2 = abs( j - center_ij );
        norme_x = x1 + x2;
        if (norme_x <= halfsize){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }
  else if ( shape == DISK ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        x1 = abs( i - center_ij );
        x2 = abs( j - center_ij );
        norme_x = sqrt(x1*x1 + x2*x2);
        if (norme_x <= halfsize){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }else if ( shape == LINE_V ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        if ( j == center_ij ){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }else if ( shape == DIAG_R ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        if ( j == 2*halfsize - i){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }else if ( shape == LINE_H){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        if ( i == center_ij ){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }else if ( shape ==  DIAG_L ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        if ( j == i ){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }else if ( shape == CROSS ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        if ( j == i || j == 2*halfsize - i ){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }

  }else if ( shape == PLUS ){
    for( int i = 0; i < mat_size; i++ ){
      for( int j = 0; j < mat_size; j++ ){
        x1 = abs( i - center_ij );
        x2 = abs( j - center_ij );
        if (x2 == 0 || x1 == 0 ){
          imd.ptr<uchar>(i)[j] = 255;
        }
      }
    }
  }
  imwrite(imdname, imd);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" shape halfsize se-name"<<endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3]);
  return EXIT_SUCCESS;
}
