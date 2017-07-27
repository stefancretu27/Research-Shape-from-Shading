#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

class Range
{
private:
    float low, high;

public:
    //getters
    float getLow(){return low;};
    float getHigh(){return high;};
    //setters
    void setLow(float new_low){this->low = new_low;};
    void setHigh(float new_high){this->high = new_high;};
};

#endif // RANGE_H_INCLUDED
