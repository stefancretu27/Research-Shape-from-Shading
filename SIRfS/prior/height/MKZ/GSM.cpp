#include "GSM.h"
#include <fstream>
#include <iomanip>

using namespace std;

void GSM::initializeGSMHeightData()
{
    //cout<<"GSM height data initializer"<<endl;

    //initialize class instance
    this->lutObj.initializeLutHeightData();
    //initialize scalar
    this->mu = 0;

    //allocate memory for vectors
    this->sigs.reserve(40);
    this->pis.reserve(40);

    //read data from files into vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/height/MKZ/sigs21.txt", this->sigs, 40, 21);

    DataFile<long double> ldFileReader;
    ldFileReader.readVector("prior/height/MKZ/pisexp.txt", this->pis, 40, numeric_limits<long double>::max());
}


void GSM::initializeGSMReflectanceGrayData()
{
    //cout<<"ReflectanceGray GSM initializer"<<endl;

    //initialize class instance
    this->lutObj.initializeLutReflectanceGrayData();
    //initialize scalar
    this->mu = 0;

    //allocate memory for vectors
    this->sigs.reserve(40);
    this->pis.reserve(40);

    //read data from files into vectors
    DataFile<double> dFileReader;
    dFileReader.readVector("prior/reflectance/gray/grayMA/sigs21.txt", this->sigs, 40, 21);

    DataFile<long double> ldFileReader;
    ldFileReader.readVector("prior/reflectance/gray/grayMA/pis_exp16.txt", this->pis, 40, numeric_limits<long double>::max());

    /*fstream fileObj;
    double temp;
    fileObj.open("prior/reflectance/gray/grayMA/sigs21.txt");

    if(fileObj.is_open())
    {
        while(fileObj>>setprecision(21)>>temp)
        {
            this->sigs.push_back(temp);
        }
    }*/

}
