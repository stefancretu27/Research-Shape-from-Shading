#ifndef KEYVALUE_H_INCLUDED
#define KEYVALUE_H_INCLUDED

template <class Type>
class KeysValue
{
private:
    Type value;
     int keyX, keyY;

public:
    //constructor: does nothing
    KeysValue(){};
    //constructor with parameters
    KeysValue(int new_keyX, int new_keyY, Type new_value)
    {
        this->value = new_value;
        this->keyX = new_keyX;
        this->keyY = new_keyY;
    };
    //copy constructor
    KeysValue(const KeysValue<Type>& source )
    {
        this->value = source.getValue();
        this->keyX = source.getKeyX();
        this->keyY = source.getKeyY();
    }

    //setters
    void setKeysValue(int new_keyX, int new_keyY, Type new_value)
    {
        this->value = new_value;
        this->keyX = new_keyX;
        this->keyY = new_keyY;
    };

    void setKeys(int new_keyX, int new_keyY)
    {
        this->keyX = new_keyX;
        this->keyY = new_keyY;
    };

    void setValue(Type new_value)
    {
        this->value = new_value;
    };

    //getters
    inline int getKeyX() const {return keyX;};
    inline int getKeyY()const {return keyY;};
    inline Type getValue() const{return value;};
    inline KeysValue& getKeysValue() const{return *this;};

    //operators' overloading
    KeysValue& operator=(const KeysValue<Type>& new_kv)
    {
        this->value = new_kv.getValue();
        this->keyX = new_kv.getKeyX();
        this->keyY = new_kv.getKeyY();

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, KeysValue& kv)
    {
        out<<kv.getKeyX()<<" "<<kv.getKeyY()<<" "<<kv.getValue();

        return out;
    };
};
#endif // KEYVALUE_H_INCLUDED
