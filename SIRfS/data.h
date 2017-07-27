#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "data_class/dataTrue.h"

class Data
{
private:
    DataTrue dt;
    Matrix2D<double> ZMedianFilterMatrix, AMedianFilterMatrix;
    Matrix2D<bool> valid;

public:
    Data(): ZMedianFilterMatrix(1,1), AMedianFilterMatrix(1,1), valid(1,1){};
    inline DataTrue& getDataTrue(){return this->dt;};
    inline Matrix2D<bool>& getValid(){return this->valid;};
    inline Matrix2D<double>& getZMedianFilterMatrix(){return this->ZMedianFilterMatrix;};
    inline Matrix2D<double>& getAMedianFilterMatrix(){return this->AMedianFilterMatrix;};
};

#endif // DATA_H_INCLUDED
