#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>

#include <morphology.hpp>

using namespace cv;
using namespace std;

void
process(const char* sename, const char* imsname, const char* imdname)
{
  cout<<"\n--------------------------------------------------\n"<<endl;
  cout<<"\n--------------- EXERCICE : EROSION ---------------\n"<<endl;
  cout<<"\n--------------------------------------------------\n"<<endl;

  //Declare variables
  //Read the image given in value
  Mat ims = imread(imsname, 0);
  Mat se = imread(sename,0);
  Mat imd(ims.size(), CV_8UC1);
  mm(se, ims, imd, minimum);

  imwrite(imdname,imd);


}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" im-se ims imd"<<std::endl;
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
