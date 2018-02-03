#ifndef REFLECTANCE_DATA_H_INCLUDED
#define REFLECTANCE_DATA_H_INCLUDED

class ReflectanceData
{
private:
    float smooth, hist, entropy, entropy_sigma;

public:
    //constructor: does nothing
    ReflectanceData(){};

    //getters
    float getSmooth(){ return smooth;};
    float getHist(){return hist;};
    float getEntropy(){return entropy;};
    float getEntropySigma(){return entropy_sigma;};

    //setters
    void setSmooth(float new_smooth)
    {
        smooth = new_smooth;
    };
    void setHist(float new_hist)
    {
        hist = new_hist;
    };
    void setEntropy(float new_entropy)
    {
        entropy = new_entropy;
    };
    void setEntropySigma(float new_entropy_sigma)
    {
        entropy_sigma = new_entropy_sigma;
    };
};

#endif // REFLECTANCE_DATA_H_INCLUDED
