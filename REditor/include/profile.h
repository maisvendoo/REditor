#ifndef     PROFILE_H
#define     PROFILE_H

#include    "project-unit.h"
#include    "profile-container.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Profile : public ProjectUnit
{

public:

    Profile(QObject *parent = Q_NULLPTR);

    ~Profile();

    void load();

    void save();

private:


    profile_container_t     container;
};

#endif // PROFILE_H
