#include "grayMA.h"

using namespace std;

void GrayMA::initializeGrayMAdata()
{
    //cout<<"ReflectanceGrayMA  initializer"<<endl;

    //initialize class instance
    this->gsm.initializeGSMReflectanceGrayData();

    //cout<<this->getGsm().sigs[3]<<endl;

    //alocate memory for vector
    this->MA_train.reserve(300000);

    //read data from files into vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/reflectance/gray/MA_train20.txt", this->MA_train, 300000, 20);
}
