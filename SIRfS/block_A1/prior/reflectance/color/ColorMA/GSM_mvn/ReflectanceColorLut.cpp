#include "ReflectanceColorLut.h"

void ReflectanceColorLut::initializeLutReflectanceColorData()
{
    //cout<<"Lut Reflectance Color initializer"<<endl;

    //initialize scalars
    this->bin_width = 3.929576889659206e-05;
    this->n_bins = 10000;
    this->bin_range.setLow(0);
    this->bin_range.setHigh(3.929537593890309);

    //allocate memory for vectors
    this->F.reserve(n_bins);

    //read data from files to vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/reflectance/color/colorMA/GSM_mvn/F16.txt", this->F, this->n_bins, 16);
}
