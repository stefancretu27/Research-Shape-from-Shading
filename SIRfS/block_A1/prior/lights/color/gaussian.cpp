#include "gaussian.h"

using namespace std;

//use constructor to allocate memory for matrix
ColorGaussian::ColorGaussian():Sigma(27,27){}

void ColorGaussian::initializeColorLaboratoryGaussianData()
{
    //cout<<"initializeColorLaboratoryGaussianData"<<endl;

    //alocate memory for vector
    mu.reserve(27);

    //read data to vector
    DataFile<long double> ldFileReader;
    ldFileReader.readVector("block_A1/prior/lights/color/laboratory/gaussian/mu_exp17.txt", this->mu, 27, 17);

    //read data to matrix
    DataFile<double> dFileReader;
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/gaussian/Sigma_exp17.txt", this->Sigma, 27, 27, 17);
}

void ColorGaussian::initializeColorNaturalGaussianData()
{
    //cout<<"initializeColorNaturalGaussianData"<<endl;

    //alocate memory for vector
    mu.reserve(27);

    //read data to vector
    DataFile<long double> ldFileReader;
    ldFileReader.readVector("block_A1/prior/lights/color/natural/gaussian/mu20.txt", this->mu, 27, 20);

    //read data to matrix
    DataFile<double> dFileReader;
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/gaussian/sigma20.txt", this->Sigma, 27, 27, 20);
}
