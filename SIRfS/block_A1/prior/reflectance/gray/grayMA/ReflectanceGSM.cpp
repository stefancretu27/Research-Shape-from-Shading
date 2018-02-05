//#include "../../../height/MKZ/GSM.h"
#include "ReflectanceGSM.h"

void ReflectanceGSM::initializeGSMReflectanceGrayData()
{
    cout<<"ReflectanceGray GSM initializer"<<endl;

    //initialize class instance
    this->lutObj.initializeLutReflectanceGrayData();
    //initialize scalar
    this->mu = 0;

    //allocate memory for vectors
    this->sigs.reserve(40);
    this->pis.reserve(40);

    //read data from files into vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/reflectance/gray/grayMA/sigs21.txt", this->sigs, 40, 21);

    DataFile<long double> ldFileReader;
    ldFileReader.readVector("block_A1/prior/reflectance/gray/grayMA/pis_exp16.txt", this->pis, 40, 21);
}
