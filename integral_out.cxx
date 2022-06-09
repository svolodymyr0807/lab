#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count;
float total, inBox;

// user defined function below
float f (float x){
  return exp(cos(x));
}
//

//function to calculate a definite integral given bounds of integration (xmin/max) & bounds of function (ymin/ymax)
float integral (float (*f)(float), float xmin, float xmax, float ymin, float ymax){
  for (count=0; count < 1000000; count++){
    float u1 = (float)rand()/(float)RAND_MAX;
    float u2 = (float)rand()/(float)RAND_MAX;

    float xcoord = ((xmax - xmin)*u1) + xmin;
    float ycoord = ((ymax - ymin)*u2) + ymin;
    float val = f(xcoord);

    total++;

    if (val > ycoord){
      inBox++;
    }
  }

  float density = inBox/total;

  std::cout<<(xmax - xmin)*(ymax - ymin)*density<<std::endl;
}


int main(int argc, char* argv[]){
float min=-2;
float max=2;
if (argc==3)
{
min=atof(argv[1]);
max=atof(argv[2]);
}
std::cout<< "RESULT: " <<std::endl;
integral(f,min,max,0,4);
}