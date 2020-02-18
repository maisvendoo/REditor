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

    void insert_before(int i, profile_element_t *element);

    void insert_after(int i, profile_element_t *element);

    void remove(int i);

    profile_element_t *elementAt(int i);

    void setInitOrdinate(double init_ordinate);

private:

    double init_ordinate;

    profile_container_t     elements;
};

#endif // PROFILE_H
