#ifndef     PROFILE_ELEMENT_H
#define     PROFILE_ELEMENT_H

#include    <QtGlobal>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct profile_element_t
{
    double  linear_coordinate;
    double  ordinate;
    double  length;
    double  inclination;
    quint32 radius;

    profile_element_t()
        : linear_coordinate(0)
        , ordinate(0)
        , length(0)
        , inclination(0)
        , radius(0)
    {

    }
};

#endif // PROFILEELEMENT_H
