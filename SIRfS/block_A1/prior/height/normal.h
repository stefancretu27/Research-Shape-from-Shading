#ifndef NORMAL_H_INCLUDED
#define NORMAL_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>

#include "../../../templates/dataFile.h"
#include "../../prior_struct_node.h"
#include "../../../helpers/validation.h"

class Normal
{
private:
    std::vector<double> X_train;       //size = 5970
    float mult, power;

public:
    //constructors
    Normal(){};
    Normal(const Normal& new_normal)
    {
        this->mult = new_normal.mult;
        this->power = new_normal.power;
        this->X_train = new_normal.X_train;
    }

    //operators overloading
    Normal& operator=(const Normal& new_normal)
    {
        this->mult = new_normal.mult;
        this->power = new_normal.power;
        this->X_train = new_normal.X_train;
        return *this;
    };

     //getters
    inline float getMult(){return this->mult;};
    inline float getPower(){return this->power;};
    inline std::vector<double> getX_train(){return this->X_train;};

    //initialize  data
    void initializeNormalData(StructNode& normal_metadata);
};

#endif // NORMAL_H_INCLUDED
