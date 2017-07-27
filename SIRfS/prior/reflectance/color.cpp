#include "color.h"

using namespace std;

ReflectanceColor::ReflectanceColor():A_train(300000,3), Aw_hist(102,102,102){}

void ReflectanceColor::initializeReflectanceColorData()
{
    //cout<<"Reflectance Color initializer"<<endl;

    //initialize class instance
    this->ma.initializeColorMAData();

    //allocate memory for vectors
    this->bin_low.assign(3, -7);        //3 ints of -7
    this->bin_high.assign(3, 4);        //3 ints of 4
    this->A_whiten.reserve(9);

    //allocate memory for matrices
    //this->A_train(300000, 3);
    //this->Aw_hist(102,102,102);

    //read data to vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/reflectance/color/A_whiten16.txt", this->A_whiten, 9, 16);

    //read data to matrices
    dFileReader.readMatrix2D("prior/reflectance/color/A_train16.txt", this->A_train, 300000, 3, 16);
    dFileReader.readMatrix3D("prior/reflectance/color/Aw_histM16.txt", this->Aw_hist, 102, 102, 102, 16);
}
