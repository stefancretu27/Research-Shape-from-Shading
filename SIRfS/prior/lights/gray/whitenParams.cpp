#include "whitenParams.h"

using namespace std;

GrayWhitenParams::GrayWhitenParams():mapp(9,9), inverse(9,9), V(9,9), D(9,9), iD(9,9), C(9,9), iC(9,9){};

void GrayWhitenParams::initializeGrayLaboratoryWhitenParamsData()
{
    //cout<<"initializeGrayLaboratoryWhitenParamsData"<<endl;

    //allocate memory for vector
    this->mean.reserve(9);

    //read data to vector
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/lights/color/laboratory/whiten_params/mean_exp16.txt", this->mean, 9, 16);

    //read data to matrices
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/map_exp16.txt", this->mapp, 9, 9, 16);
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/inverse_exp16.txt", this->inverse, 9, 9, 16);
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/V_exp16.txt", this->V, 9, 9, 16);
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/D18.txt", this->D, 9, 9, 18);
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/iD_exp16.txt", this->iD, 9, 9, 16);
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/C_exp16.txt", this->C, 9, 9, 16);
    dFileReader.readMatrix2D("prior/lights/gray/laboratory/whiten_params/iC_exp16.txt", this->iC, 9, 9, 16);
}

void GrayWhitenParams::initializeGrayNaturalWhitenParamsData()
{
    //cout<<"initializeGrayNaturalWhitenParamsData"<<endl;

    //allocate memory for vector
    this->mean.reserve(9);

    //read data to vector
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/lights/gray/natural/whiten_params/mean20.txt", this->mean, 9, 20);

    //read data to matrices
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/map20.txt", this->mapp, 9, 9, 20);
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/inverse20.txt", this->inverse, 9, 9, 20);
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/V20.txt", this->V, 9, 9, 20);
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/D18.txt", this->D, 9, 9, 18);
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/iD16.txt", this->iD, 9, 9, 16);
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/C20.txt", this->C, 9, 9, 20);
    dFileReader.readMatrix2D("prior/lights/gray/natural/whiten_params/iC18.txt", this->mapp, 9, 9, 18);
}
