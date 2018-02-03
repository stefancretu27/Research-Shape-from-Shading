#ifndef NORMAL_H_INCLUDED
#define NORMAL_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>

#include "../../templates/dataFile.h"

class Normal
{
private:
    std::vector<double> x_train;       //size = 5970
    float mult, power;

public:
     //getters
    inline float getMult(){return this->mult;};
    inline float getPower(){return this->power;};
    inline std::vector<double> &getX_train(){return this->x_train;};

    //initialize  data
    void initializeNormalData();
};

#endif // NORMAL_H_INCLUDED
