#ifndef HEIGHT_DATA_H_INCLUDED
#define HEIGHT_DATA_H_INCLUDED

class HeightData
{
private:
    float smooth, slant, contour_mult, contour_power, init, init_power;

public:
    //constructor: does nothing
    HeightData(){};

    //setters
    void setSmooth(float new_smooth)
    {
        smooth = new_smooth;
    };
    void setSlant(float new_slant)
    {
        slant  = new_slant;
    };
    void setContourMult(float new_contour_mult)
    {
        contour_mult = new_contour_mult;
    };
    void setContourPower(float new_contour_power)
    {
        contour_power = new_contour_power;
    };
    void setInit(float new_init)
    {
        init = new_init;
    };
    void setInitPower(float new_init_power)
    {
        init_power = new_init_power;
    };

    //getters
    float getSmooth() {return smooth;};
    float getSlant() {return slant;};
    float getContourMult() {return contour_mult;};
    float getContourPower() {return contour_power;};
    float getInit() {return init;};
    float getInitPower() {return init_power;};
};

#endif // HEIGHT_DATA_H_INCLUDED
