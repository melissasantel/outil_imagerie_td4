#include <iostream>
#include <cstdlib>

#include <morphology.hpp>

using namespace cv;
using namespace std;

void
process(const char* sename, const char* imsname, const char* imdname)
{
  cout<<"\n--------------------------------------------------\n"<<endl;
  cout<<"\n--------------- EXERCICE : CLOSING ---------------\n"<<endl;
  cout<<"\n--------------------------------------------------\n"<<endl;

  //-- Declare variables
  //-- And read the image given in value
  Mat ims = imread(imsname, 0);
  Mat se = imread(sename,0);
  Mat imd_inter(ims.size(), CV_8UC1);
  Mat imd(ims.size(), CV_8UC1);
  //-- Check if the image exist
  if(!ims.data || !se.data){
    cerr<<"Image not found, exit"<<endl;
    exit(EXIT_FAILURE);
  }
  //-- Make the dilation
  mm(se, ims, imd_inter, maximum);
  //-- Make the erosion
  mm(se,imd_inter,imd,minimum);
  //-- Save the image after closing
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