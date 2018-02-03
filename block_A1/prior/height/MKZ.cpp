#include "MKZ.h"

using namespace std;

void MKZ::initilalizeMKZData()
{
    //cout<<"MKZ initializer"<<endl;

    //initialize class instance
    this->gsm.initializeGSMHeightData();

    //allocate memory for vector
    this->mkz_train.reserve(300000);

    //read data from file into vector
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/height/mkz_train21.txt", this->mkz_train, 300000, 21);
}
