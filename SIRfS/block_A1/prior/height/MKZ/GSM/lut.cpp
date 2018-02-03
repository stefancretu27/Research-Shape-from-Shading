#include "lut.h"

using namespace std;

void Lut::initializeLutHeightData()
{
    //cout<<"Lut height data initializer"<<endl;

    //initialize scalars
    this->bin_width = 2.193371460054008e-04;
    this->n_bins = 20000;
    this->bin_range.setLow(-2.193261791481005);
    this->bin_range.setHigh(2.193261791481005);

    //allocate memory for vectors
    this->F_LL.reserve(n_bins);
    this->F_cost.reserve(n_bins);
    this->N_train.reserve(n_bins);

    //read data from files to vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/height/MKZ/GSM/F_LL15.txt", this->F_LL, this->n_bins, 15);
    dFileReader.readVector("block_A1/prior/height/MKZ/GSM/F_cost15.txt", this->F_cost, this->n_bins, 15);

    DataFile<unsigned int> uFileReader;
    uFileReader.readVector("block_A1/prior/height/MKZ/GSM/N_train.txt", this->N_train, this->n_bins, 0);
}


void Lut::initializeLutReflectanceGrayData()
{
    //cout<<"Lut Reflectance Gray initializer"<<endl;

    //initialize scalars
    this->bin_width = 3.925566228506992e-04;
    this->n_bins = 20000;
    this->bin_range.setLow(-3.925369950195567);
    this->bin_range.setHigh(3.925369950195567);

    //allocate memory for vectors
    this->F_LL.reserve(n_bins);
    this->F_cost.reserve(n_bins);
    this->N_train.reserve(n_bins);

    //read data from files to vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/reflectance/gray/grayMA/GSM/F_LL15.txt", this->F_LL, this->n_bins, 15);
    dFileReader.readVector("block_A1/prior/reflectance/gray/grayMA/GSM/F_cost15.txt", this->F_cost, this->n_bins, 15);

    DataFile<unsigned int> uFileReader;
    uFileReader.readVector("block_A1/prior/reflectance/gray/grayMA/GSM/N_train.txt", this->N_train, this->n_bins, 0);
}
