#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum Comparison
{
    Equal,
    NonEqual,
    LessThan,
    LessThanOrEqual,
    GreaterThanOrEqual,
    GreaterThan
};

enum Operation
{
    Sum,
    Substract,
    Multiply,
    Divide,
    Pow,
    Exp
};

enum DataType
{
    Bool,
    Int,
    Float,
    Double
};

enum ArrayType
{
    Vector,
    Matrix2d
};

#endif // ENUMS_H_INCLUDED
