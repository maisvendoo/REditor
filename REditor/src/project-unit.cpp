#include    "project-unit.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectUnit::ProjectUnit(QObject *parent) : QObject(parent)
  , is_changed(false)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectUnit::~ProjectUnit()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool ProjectUnit::isChanged() const
{
    return is_changed;
}
