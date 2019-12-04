#include <iostream>
#include <cstdlib>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int
_find(int p, int* roots)
{
  while(roots[p] != p)
    p = roots[p];
  return p;
}

int
_union(int r0, int r1, int* roots)
{
  if(r0 == r1) return r0;
  if(r0 == -1) return r1;
  if(r1 == -1) return r0;
  if(r0 <  r1){
    roots[r1] = r0;
    return r0;
  }else{
    roots[r0]=r1;
    return r1;
  }
}

int
_add(int p, int r, int* roots)
{
  if(r==-1)
    roots[p]=p;
  else
    roots[p]=r;
  return roots[p];
}

void
process(const char* imsname, const char* regname, const char* colorname)
{
  cout<<"\n---------------------------------------------------------\n"<<endl;
  cout<<"\n--------------- EXERCICE : LABELING-COLOR ---------------\n"<<endl;
  cout<<"\n---------------------------------------------------------\n"<<endl;

  Mat ims = imread(imsname);
  Size ims_size = ims.size();
  if(!ims.data){
    cerr<<"Image not found, exit"<<endl;
    exit(EXIT_FAILURE);
  }

  cvtColor(ims, ims, CV_BGR2GRAY);

  int* roots = new int[ims.total()]; //get numbers of pixels
  int  rows  = ims.rows;
  int  cols  = ims.cols;
  int p      = 0;
  int r      = -1;
  uchar* ps  = ims.data; //get data from ims
  int NB_COLORS = 20;
  RNG rng(125862);

  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      r = -1;

      if( j>0 && (*(ps-1)==(*ps)) )
	r = _union( _find(p-1, roots), r, roots);

      if( (i>0 && j>0) && (*(ps-1-cols)==(*ps)) )
	r = _union( _find(p-1-cols, roots), r, roots);

      if( i>0 && (*(ps-cols) == (*ps)) )
	r = _union(_find(p-cols, roots), r, roots);

      if( (j<(cols-1) && i>0) && (*(ps+1-cols)==(*ps)) )
	r = _union(_find(p+1-cols, roots), r, roots);

      r = _add(p, r, roots);

      p++;
      ps++;
    }
  }

  for(p=0; p<rows*cols; p++){
    roots[p] = _find(p, roots);
  }
  //-- Create the image cell_r;
  Mat imd_cellr (ims_size, CV_8UC1);
  //-- Create Mat corresponding image cell_rh's equalized histogram;
  Mat imd_cellrh (ims_size, CV_8UC1);
  //-- Create Mat corresping to the colored image ;
  Mat imd_cellc(ims_size,CV_8UC3);

  int l=0;
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      int p = i*cols+j;
      if(roots[p]==p)
	roots[p] = l++;
      else
	roots[p] = roots[roots[p]];
  imd_cellr.ptr<uchar>(i)[j] = roots[p];
    }
  }
  NB_COLORS = l;
  //--Save the region map
  imwrite(regname,imd_cellr);

  //-- Make the eqalize histogram of the imd_cellr to fill imd_cellrh
  equalizeHist(imd_cellr, imd_cellrh);
  //-- Save the region map with histogram
  imwrite("cell-r-histogram.png",imd_cellrh);

  //-- Make the region map with fake colors
  vector<Vec3b> colors;
  for (int i = 0; i < NB_COLORS; i++){
    Vec3b color(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
    colors.push_back(color);
  }

  for (int i=0; i<ims_size.height; i++){
    for (int j=0; j<ims_size.width; j++){
      int current_color = (int)imd_cellr.ptr<uchar>(i)[j];
      if(current_color > 0)
        imd_cellc.ptr<Vec3b>(i)[j] = colors[current_color];
    }

  }
  //-- Save the region map colored
  imwrite(colorname,imd_cellc);

  cout<<"labeling: "<< l << " components detected"<<endl;
  delete [] roots;
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1],argv[2],argv[3]);
  return EXIT_SUCCESS;
}
