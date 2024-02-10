#include <cmath>
#include "Vec3.h"

Vec3::Vec3() : values{0} {return;}

Vec3::Vec3(const float x, const float y, const float z) 
{
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

void Vec3::set(const char dimension, const float value)
{
    switch(dimension)
    {
        case X:
            values[0] = value;
            break;
        case Y:
            values[1] = value;
            break;
        case Z:
            values[2] = value;
            break;
        default:
            throw(false);
            break;
    }
    return;
}
float Vec3::get(const char dimension)
{
    switch(dimension)
    {
        case X:
            return values[0];
            break;
        case Y:
            return values[1];
            break;
        case Z:
            return values[2];
            break;
        default:
            throw(false);
            break;
    }
}

float Vec3::length() const
{
    return std::sqrt((values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]));
}

Vec3 Vec3::operator-()
{
   // Vec3 temp = *this;
   // temp.values[0] = -temp.values[0];
   // temp.values[1] = -temp.values[1];
   // temp.values[2] = -temp.values[2];
   // return temp;
   return Vec3(-values[0], -values[1], -values[2]);
}
float Vec3::operator*(const Vec3 & op2)
{
    return (values[0] * op2.values[0]) 
    + (values[1] * op2.values[1]) 
    + (values[2] * op2.values[2]);
}

Vec3 & Vec3::operator*=(const float op2)
{
    values[0] *= op2;
    values[1] *= op2;
    values[2] *= op2;
    return *this;
}

Vec3 & Vec3::operator/=(const float op2)
{
    values[0] /= op2;
    values[1] /= op2;
    values[2] /= op2;
    return *this;
}

Vec3 Vec3::operator+(const Vec3 & op2)
{
    Vec3 temp = Vec3();
    temp.values[0] = values[0] + op2.values[0];
    temp.values[1] = values[1] + op2.values[1];
    temp.values[2] = values[2] + op2.values[2];
    return temp;
}

Vec3 & Vec3::operator+=(const Vec3 & op2)
{
    values[0] += op2.values[0];
    values[1] += op2.values[1];
    values[2] += op2.values[2];
    return *this;
}

Vec3 Vec3::operator-(const Vec3 & op2)
{
    Vec3 temp = Vec3();
    temp.values[0] = values[0] - op2.values[0];
    temp.values[1] = values[1] - op2.values[1];
    temp.values[2] = values[2] - op2.values[2];
    return temp;
}

Vec3 & Vec3::operator-=(const Vec3 & op2)
{
    values[0] += op2.values[0];
    values[1] += op2.values[1];
    values[2] += op2.values[2];
    return *this;
}

bool Vec3::operator==(const Vec3 & op2)
{
    return (values[0] == op2.values[0]
        && values[1] == op2.values[1]
        && values[2] == op2.values[2]);
}

bool Vec3::operator!=(const Vec3 & op2)
{
    return (values[0] != op2.values[0]
        || values[1] != op2.values[1]
        || values[2] != op2.values[2]);
}


// Friend operators
Vec3 operator*(const Vec3 & op1, const float op2)
{
    Vec3 temp = Vec3(op1.values[0] * op2, op1.values[1] * op2, op1.values[2] * op2);
    return temp;
}

Vec3 operator*(const float op1, const Vec3 & op2)
{
    Vec3 temp = Vec3(op2.values[0] * op1, op2.values[1] * op1, op2.values[2] * op1);
    return temp;
}

Vec3 operator/(const Vec3 & op1, const float op2)
{
    Vec3 temp = Vec3(op1.values[0] / op2, op1.values[1] / op2, op1.values[2] / op2);
    return temp;
}

Vec3 operator/(const float op1, const Vec3 & op2)
{
    Vec3 temp = Vec3(op2.values[0] / op1, op2.values[1] / op1, op2.values[2] / op1);
    return temp;
}
