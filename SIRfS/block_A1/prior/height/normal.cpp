#include "normal.h"

using namespace std;

void Normal::initializeNormalData()
{
    //cout<<"Normal initializer"<<endl;

    //initialize scalars
    this->mult = 2.949999999999999;
    this->power = 0.75;

    //allocate memory for vector
    this->x_train.reserve(5970);

    //read data from file into vector
    DataFile<double> dFileReader;
    dFileReader.readVector("block_A1/prior/height/x_train17.txt", this->x_train, 5970, 17);
}
