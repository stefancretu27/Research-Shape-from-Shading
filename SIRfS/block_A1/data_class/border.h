#ifndef BORDER_H_INCLUDED
#define BORDER_H_INCLUDED

#include <vector>
#include "../../templates/matrix2D_cuda.h"

class Border
{
private:
    std::vector<double> Idx;
    Matrix2D<double> Position;
    Matrix2D<double> Normal;
    Matrix2D<double> Tangent;

public:
    //contructor initializes matrixes to point to one element. They get resized when new matrixesare assigned to them
    Border():Position(), Normal(),Tangent(){};
    //getters
    inline std::vector<double>& getIdx(){return this->Idx;};
    inline Matrix2D<double>& getPosition(){return this->Position;};
    inline Matrix2D<double>& getNormal(){return this->Normal;};
    inline Matrix2D<double>& getTangent(){return this->Tangent;};
    //setters
    inline void setIdx(std::vector<double>& in){this->Idx = in;};
    inline void setPosition(Matrix2D<double>& in){this->Position = in;};
    inline void setNormal(Matrix2D<double>& in){this->Normal = in;};
    inline void setTangent(Matrix2D<double>& in){this->Tangent = in;};
};

#endif // BORDER_H_INCLUDED
