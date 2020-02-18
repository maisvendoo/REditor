#include    "project.h"

#include    "project-unit.h"
#include    "profile.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Project::Project(QObject *parent) : QObject(parent)
  , name("new_route")
  , title("")
  , description("")
  , is_changed(false)
  , profile(new Profile)
{
    units.push_back(profile);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Project::~Project()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Project::load()
{
    for (ProjectUnit *unit : units)
    {
        if (unit != Q_NULLPTR)
            unit->load();
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Project::save()
{
    for (ProjectUnit *unit : units)
    {
        if (unit != Q_NULLPTR)
            unit->save();
    }

    is_changed = false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Project::setName(QString name)
{
    this->name = name;

    is_changed = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Project::setTitle(QString title)
{
    this->title = title;

    is_changed = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Project::setDescription(QString description)
{
    this->description = description;

    is_changed = true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Project::setProjectDir(QString project_dir)
{
    this->project_dir = project_dir;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Project::isChanged()
{
    for (ProjectUnit *unit : units)
    {
        is_changed = is_changed || unit->isChanged();
    }

    return is_changed;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString Project::getName() const
{
    return name;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString Project::getTitle() const
{
    return title;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString Project::getDescription() const
{
    return description;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
QString Project::getProjectDir() const
{
    return project_dir;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Profile *Project::getProfile()
{
    return profile;
}
