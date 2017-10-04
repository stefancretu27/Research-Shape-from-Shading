#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "data_class/dataTrue.h"
#include "templates/keyValue.h"

class Data
{
private:
    DataTrue dt;
    Matrix2D< KeysValue <double> >* ZMedianFilterMatrix;
    Matrix2D< KeysValue <double> >* AMedianFilterMatrix;
    Matrix2D<bool> valid;

public:
    Data(): valid(1,1){};       //ZMedianFilterMatrix(1,1), AMedianFilterMatrix(1,1),
    inline DataTrue& getDataTrue(){return this->dt;};
    inline Matrix2D<bool>& getValid(){return this->valid;};
    inline Matrix2D<KeysValue<double> >** getZMedianFilterMatrixAddress(){return &ZMedianFilterMatrix;};
    inline Matrix2D<KeysValue<double> >** getAMedianFilterMatrixAddress(){return &AMedianFilterMatrix;};
    inline Matrix2D<KeysValue<double> >* getZMedianFilterMatrix(){return ZMedianFilterMatrix;};
    inline Matrix2D<KeysValue<double> >* getAMedianFilterMatrix(){return AMedianFilterMatrix;};
};

#endif // DATA_H_INCLUDED
