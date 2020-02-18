//------------------------------------------------------------------------------
//
//      Элемент профиля пути
//
//------------------------------------------------------------------------------
#ifndef     PROFILE_ELEMENT_H
#define     PROFILE_ELEMENT_H

#include    <QString>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct zds_profile_element_t
{
    qint32  ordinate;
    qint32  inclination;
    qint16  radius;
    qint16  left_height;
    qint16  right_height;
    qint8   current_kind;
    qint8   is_double_track;
    qint16  left_forest_type;
    qint16  left_forest_removal;
    qint16  right_forest_type;
    qint16  right_forest_removal;


    zds_profile_element_t()
    {

    }
};

#endif // PROFILE_ELEMENT_H
