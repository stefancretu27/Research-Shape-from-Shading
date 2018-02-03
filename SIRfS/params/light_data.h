#ifndef LIGHT_DATA_H_INCLUDED
#define LIGHT_DATA_H_INCLUDED

class LightData
{
private:
    float gaussian;

public:
    //constructor: does nothing
    LightData(){};
    //getter
    float getGaussian(){return gaussian;};
    //setter
    void setGaussian(float new_gaussian)
    {
        gaussian = new_gaussian;
    };
};

#endif // LIGHT_DATA_H_INCLUDED
