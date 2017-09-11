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
        value = new_value;
        keyX = new_keyX;
        keyY = new_keyY;
    };

    void setKeys(int new_keyX, int new_keyY)
    {
        keyX = new_keyX;
        keyY = new_keyY;
    };

    void setValue(Type new_value)
    {
        value = new_value;
    };

    //getters
    inline int getKeyX() const {return keyX;};
    inline int getKeyY()const {return keyY;};
    inline Type getValue() const{return value;};

    //operators' overloading
    KeysValue& operator=(const KeysValue<Type>& new_kv)
    {
        value = new_kv.getValue();
        keyX = new_kv.getKeyX();
        keyY = new_kv.getKeyY();

        return *this;
    }
};

#endif // KEYVALUE_H_INCLUDED
