#ifndef GSM_MVN_H_INCLUDED
#define GSM_MVN_H_INCLUDED

#include "GSM_mvn/ReflectanceColorLut.h"
#include "../../../../../templates/matrix2D_cuda.h"

class GSM_mvn
{
private:
    ReflectanceColorLut lut;
    double LL_zero;
    std::vector<double> pis, vars, logmults;       //size = 40
    Matrix2D<double> Sigma, Sigma_inv, Sigma_whiten, Sigma_R;      //size [3][3]

public:
    //operators overloading
    GSM_mvn(){};
    GSM_mvn(const GSM_mvn& input)
    {
        this->lut = input.lut;
        this->LL_zero = input.LL_zero;
        this->pis = input.pis;
        this->vars = input.vars;
        this->logmults = input.logmults;
        this->Sigma = input.Sigma;
        this->Sigma_inv = input.Sigma_inv;
        this->Sigma_whiten = input.Sigma_whiten;
        this->Sigma_R = input.Sigma_R;
    };

    //operators overloading
    GSM_mvn& operator=(const GSM_mvn& input)
    {
        this->lut = input.lut;
        this->LL_zero = input.LL_zero;
        this->pis = input.pis;
        this->vars = input.vars;
        this->logmults = input.logmults;
        this->Sigma = input.Sigma;
        this->Sigma_inv = input.Sigma_inv;
        this->Sigma_whiten = input.Sigma_whiten;
        this->Sigma_R = input.Sigma_R;
        return *this;
    };

    //getters
    inline  ReflectanceColorLut& getLut(){return this->lut;};
    inline  double getLLzero(){return this->LL_zero;};
    inline  std::vector<double>& getPis(){return this->pis;};
    inline  std::vector<double>& getVars(){return this->vars;};
    inline  std::vector<double>& getLogmults(){return this->logmults;};
    inline Matrix2D<double>& getSigma(){return this->Sigma;};
    inline Matrix2D<double>& getSigma_inv(){return this->Sigma_inv;};
    inline Matrix2D<double>& getSigma_whiten(){return this->Sigma_whiten;};
    inline Matrix2D<double>& getSigma_R(){return this->Sigma_R;};

    //initialize data
    void initializeGSM_mvnData(StructNode& color_ma_gsm_metadata);
};

#endif // GSM_MVN_H_INCLUDED
