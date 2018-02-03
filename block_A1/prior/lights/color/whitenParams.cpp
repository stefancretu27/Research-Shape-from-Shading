#include "whitenParams.h"

using namespace std;

void ColorWhitenParams::initializeColorLaboratoryWhitenParamsData()
{
    //cout<<"initializeColorLaboratoryWhitenParamsData"<<endl;

    //allocate memory for vector
    this->mean.reserve(27);

    //read data to vector
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/lights/color/laboratory/whiten_params/mean_exp16.txt", this->mean, 27, 16);

    //read data to matrices
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/map_exp16.txt", this->mapp, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/inverse_exp16.txt", this->inverse, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/V_exp16.txt", this->V, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/D20.txt", this->D, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/iD16.txt", this->iD, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/C_exp16.txt", this->C, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/laboratory/whiten_params/iC_exp16.txt", this->iC, 27, 27, 16);
}

void ColorWhitenParams::initializeColorNaturalWhitenParamsData()
{
    //cout<<"initializeColorNaturalWhitenParamsData"<<endl;

    //allocate memory for vector
    this->mean.reserve(27);

    //read data to vector
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/lights/color/natural/whiten_params/mean20.txt", this->mean, 27, 20);

    //read data to matrices
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/map20.txt", this->mapp, 27, 27, 20);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/inverse21.txt", this->inverse, 27, 27, 21);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/V19.txt", this->V, 27, 27, 19);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/D20.txt", this->D, 27, 27, 20);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/iD16.txt", this->iD, 27, 27, 16);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/C21.txt", this->C, 27, 27, 21);
    dFileReader.readMatrix2D("block_A1/prior/lights/color/natural/whiten_params/iC15.txt", this->mapp, 27, 27, 15);
}
