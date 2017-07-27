#include "gray.h"

using namespace std;

void ReflectanceGray::initializeReflectanceGrayData()
{
    //cout<<"ReflectanceGray initializer"<<endl;

    //initialize scalars
    this->range.setLow(-7);
    this->range.setHigh(4);

    //initialize class instance
    this->MA.initializeGrayMAdata();

    //alocate memory for vectors
    this->A_spline.reserve(256);
    this->A_train.reserve(300000);

    //read data from files into vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/reflectance/A_train15.txt", this->A_train, 300000, 15);
    dFileReader.readVector("prior/reflectance/A_spline15.txt", this->A_spline, 256, 15);
}
