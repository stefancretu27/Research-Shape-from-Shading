#include "gaussian.h"

//use constructor to allocate memory for matrix
GrayGaussian::GrayGaussian():Sigma(9, 9){}

void GrayGaussian::initializeGrayLaboratoryGaussianData()
{
    //cout<<"initializeGrayLaboratoryGaussianData"<<endl;

    //alocate memory for vector
    mu.reserve(9);

    //read data to vector
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/lights/gray/laboratory/gaussian/mu_exp16.txt", this->mu, 9, 16);

    //read data to matrix
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/gaussian/sigma_exp16.txt", this->Sigma, 9, 9, 16);
}

void GrayGaussian::initializeGrayNaturalGaussianData()
{
    //cout<<"initializeGrayNaturalGaussianData"<<endl;

    //alocate memory for vector
    mu.reserve(9);

    //read data to vector
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/lights/gray/natural/gaussian/mu20.txt", this->mu, 9, 20);

    //read data to matrix
    dFileReader.readMatrix2D("prior/lights/gray/natural/gaussian/Sigma20.txt", this->Sigma, 9, 9, 20);
}
