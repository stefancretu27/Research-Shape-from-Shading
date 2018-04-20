#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "data_class/dataTrue.h"
#include "data_class/border.h"
#include "../templates/keyValue.h"
#include "prior.h"

class Data
{
private:
    DataTrue dt;
    Border border;
    Prior prior;
    Matrix2D<double>* ZMedianFilterMat;
    Matrix2D<double>* AMedianFilterMat;
    Matrix2D<double>* ZMedianFilterMatT;
    Matrix2D<double>* AMedianFilterMatT;
    Matrix2D<bool> valid;

public:
    Data():valid(){};
    //getters
    inline DataTrue& getDataTrue(){return this->dt;};
    inline Border& getBorder(){return this->border;};
    inline Prior& getPrior(){return this->prior;};
    inline Matrix2D<bool>& getValid(){return this->valid;};

    //matrices getters
    inline Matrix2D<double>** getZMedianFilterMatAddress(){return &ZMedianFilterMat;};
    inline Matrix2D<double>** getAMedianFilterMatAddress(){return &AMedianFilterMat;};
    inline Matrix2D<double> * getZMedianFilterMat(){return ZMedianFilterMat;};
    inline Matrix2D<double> * getAMedianFilterMat(){return AMedianFilterMat;};
    //transpose getters
    inline Matrix2D<double>** getZMedianFilterMatTAddress(){return &ZMedianFilterMatT;};
    inline Matrix2D<double>** getAMedianFilterMatTAddress(){return &AMedianFilterMatT;};
    inline Matrix2D<double> * getZMedianFilterMatT(){return ZMedianFilterMatT;};
    inline Matrix2D<double> * getAMedianFilterMatT(){return AMedianFilterMatT;};

    //setters
    inline void setValid(Matrix2D<bool> &input){this->valid = input;};
    inline void setPrior(Prior &input){this->prior = input;};
};

#endif // DATA_H_INCLUDED
