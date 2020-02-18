#ifndef     PROJECT_WIZARD_H
#define     PROJECT_WIZARD_H

#include    <QMainWindow>

class Project;

namespace Ui
{
    class ProjectWizard;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ProjectWizard : public QMainWindow
{
    Q_OBJECT

public:

    explicit ProjectWizard(Project *project = Q_NULLPTR, QWidget *parent = nullptr);

    ~ProjectWizard();

private:

    Ui::ProjectWizard   *ui;

    Project             *project;

private slots:

    void slotCreate();

    void slotCancel();
};

#endif // PROJECT_WIZARD_H
