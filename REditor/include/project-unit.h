#ifndef     PROJECT_UNIT_H
#define     PROJECT_UNIT_H

#include    <QObject>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ProjectUnit : public QObject
{
    Q_OBJECT

public:

    ProjectUnit(QObject *parent = Q_NULLPTR);

    virtual ~ProjectUnit();

    virtual void load() = 0;

    virtual void save() = 0;

    bool isChanged() const;

protected:

    bool    is_changed;
};

#endif // PROJECT_UNIT_H
