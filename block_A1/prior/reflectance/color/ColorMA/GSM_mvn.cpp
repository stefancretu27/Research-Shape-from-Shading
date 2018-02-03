#include "GSM_mvn.h"

//call Matrix2D constructors to allocate memory for matrices
GSM_mvn::GSM_mvn():Sigma(3,3), Sigma_inv(3,3), Sigma_whiten(3, 3), Sigma_R(3,3){};

void GSM_mvn::initializeGSM_mvnData()
{
    //cout<<"GSM_mvn initializer"<<endl;

    //initialize the scalar
    this->LL_zero = 10.094392329265354;

    //initialize class instance
    this->lut.initializeLutReflectanceColorData();

    //allocate memory for vectors
    this->logmults.reserve(40);
    this->pis.reserve(40);
    this->vars.reserve(40);

    //allocate memory for matrices
    /*this->Sigma(3, 3);
    this->Sigma_inv(3,3);
    this->Sigma_whiten(3,3);
    this->Sigma_R(3,3);*/

    //read data to vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/reflectance/color/ColorMA/logmults16.txt", this->logmults, 40, 16);
    dFileReader.readVector("block_A1/prior/reflectance/color/ColorMA/vars_exp15.txt", this->vars, 40, 15);
    dFileReader.readVector("block_A1/prior/reflectance/color/ColorMA/pis21.txt", this->pis, 40, 21);

    //read data to matrices
    dFileReader.readMatrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma16.txt", this->Sigma, 3, 3, 16);
    dFileReader.readMatrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma_inv16.txt", this->Sigma_inv, 3, 3, 16);
    dFileReader.readMatrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma_R16.txt", this->Sigma_R, 3, 3, 16);
    dFileReader.readMatrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma_whiten16.txt", this->Sigma_whiten, 3, 3, 16);
}
