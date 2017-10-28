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

    Data(): valid(1,1)
    {
        ZMedianFilterMat = new Matrix2D< KeysValue <double> >(1,1);
        AMedianFilterMat = new Matrix2D< KeysValue <double> >(1,1);
    };       //ZMedianFilterMatrix(1,1), AMedianFilterMatrix(1,1),

    //getters
    inline DataTrue& getDataTrue(){return this->dt;};
    inline Border& getBorder(){return this->border;};
    inline Matrix2D<bool>& getValid(){return this->valid;};
    //matrices getetrs
    inline Matrix2D<KeysValue<double> >** getZMedianFilterMatAddress(){return &ZMedianFilterMat;};
    inline Matrix2D<KeysValue<double> >** getAMedianFilterMatAddress(){return &AMedianFilterMat;};
    inline Matrix2D<KeysValue<double> >* getZMedianFilterMat(){return ZMedianFilterMat;};
    inline Matrix2D<KeysValue<double> >* getAMedianFilterMat(){return AMedianFilterMat;};
    //transpose gtters
    inline Matrix2D<KeysValue<double> >** getZMedianFilterMatTAddress(){return &ZMedianFilterMatT;};
    inline Matrix2D<KeysValue<double> >** getAMedianFilterMatTAddress(){return &AMedianFilterMatT;};
    inline Matrix2D<KeysValue<double> >* getZMedianFilterMatT(){return ZMedianFilterMatT;};
    inline Matrix2D<KeysValue<double> >* getAMedianFilterMatT(){return AMedianFilterMatT;};
};

#endif // DATA_H_INCLUDED
