#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "data_class/dataTrue.h"
#include "data_class/border.h"
#include "templates/keyValue.h"

class Data
{
public:
    DataTrue dt;
    Border border;
    Matrix2D< KeysValue <double> >* ZMedianFilterMat;
    Matrix2D< KeysValue <double> >* AMedianFilterMat;
    Matrix2D< KeysValue <double> >* ZMedianFilterMatT;
    Matrix2D< KeysValue <double> >* AMedianFilterMatT;
    Matrix2D<bool> valid;

    Data()
    {
        //ZMedianFilterMat = new Matrix2D< KeysValue <double> >(1,1);
        //AMedianFilterMat = new Matrix2D< KeysValue <double> >(1,1);
    };

    //getters
    inline DataTrue& getDataTrue(){return this->dt;};
    inline Border& getBorder(){return this->border;};
    inline Matrix2D<bool>& getValid(){return this->valid;};
    //matrices getters
    inline Matrix2D<KeysValue<double> >** getZMedianFilterMatAddress(){return &ZMedianFilterMat;};
    inline Matrix2D<KeysValue<double> >** getAMedianFilterMatAddress(){return &AMedianFilterMat;};
    inline Matrix2D<KeysValue<double> >* getZMedianFilterMat(){return ZMedianFilterMat;};
    inline Matrix2D<KeysValue<double> >* getAMedianFilterMat(){return AMedianFilterMat;};
    //transpose getters
    inline Matrix2D<KeysValue<double> >** getZMedianFilterMatTAddress(){return &ZMedianFilterMatT;};
    inline Matrix2D<KeysValue<double> >** getAMedianFilterMatTAddress(){return &AMedianFilterMatT;};
    inline Matrix2D<KeysValue<double> >* getZMedianFilterMatT(){return ZMedianFilterMatT;};
    inline Matrix2D<KeysValue<double> >* getAMedianFilterMatT(){return AMedianFilterMatT;};

    //setters
    inline void setValid(Matrix2D<bool>& in){this->valid = in;};
};

#endif // DATA_H_INCLUDED
