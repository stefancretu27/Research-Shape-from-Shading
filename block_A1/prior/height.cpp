#include "height.h"

using namespace std;

void Height::initializeHeightData()
{
    //cout<<"Height initializer"<<endl;

    //initialize classes instances
    this->mkz.initilalizeMKZData();
    this->normal.initializeNormalData();

    //allocate memory for vector
    this->nz_train.reserve(300000);

    //read data from file into vector
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/nz_train17.txt", this->nz_train, 300000, 17);
}
