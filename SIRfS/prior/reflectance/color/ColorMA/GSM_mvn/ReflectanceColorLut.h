#ifndef REFLECTANCECOLORLUT_H_INCLUDED
#define REFLECTANCECOLORLUT_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>

#include "../../../../../range.h"
#include "../../../../../templates/dataFile.h"

class ReflectanceColorLut
{
private:
    double bin_width;
    std::vector<double>  F;       //size = 10000
    int n_bins;
    Range bin_range;

public:
    //getters
    inline  double getBin_width(){return this->bin_width;};
    inline int getN_bins(){return this->n_bins;};
    inline  Range& getBin_range(){return this->bin_range;};
    inline std::vector<double>& getF() {return this->F;};

    //initialize reflectance color data
    void initializeLutReflectanceColorData();
};


#endif // REFLECTANCECOLORLUT_H_INCLUDED
