#ifndef KEYVALUE_H_INCLUDED
#define KEYVALUE_H_INCLUDED

template <class Type>
class KeysValue
{
private:
    Type value;
     int keyX, keyY;

public:
    //constructor
    KeysValue(){};

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

    int getKeyX(){return keyX;};
    int getKeyY(){return keyY;};
    Type getValue(){return value;};

    KeysValue& operator=(KeysValue<Type>& new_kv)
    {
        value = new_kv.getValue();
        keyX = new_kv.getKeyX();
        keyY = new_kv.getKeyY();

        return *this;
    }
};

#endif // KEYVALUE_H_INCLUDED
