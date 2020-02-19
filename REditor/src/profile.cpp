#include    "profile.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Profile::Profile(QObject *parent) : ProjectUnit(parent)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Profile::~Profile()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Profile::load()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Profile::save()
{
    is_changed = false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Profile::insert_before(int i, profile_element_t *element)
{
    elements.insert(i, element);

    is_changed = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Profile::insert_after(int i, profile_element_t *element)
{
    elements.insert(i + 1, element);

    is_changed = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Profile::remove(int i)
{
    elements.removeAt(i);

    is_changed = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
profile_element_t *Profile::elementAt(int i)
{
    return elements.at(i);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Profile::setInitOrdinate(double init_ordinate)
{
    this->init_ordinate = init_ordinate;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
profile_container_t Profile::getElements()
{
    return elements;
}
