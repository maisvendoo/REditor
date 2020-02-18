#ifndef     PROJECT_WIZARD_H
#define     PROJECT_WIZARD_H

#include    <QDialog>

class Project;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace Ui
{
    class ProjectWizard;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ProjectWizard : public QDialog
{
    Q_OBJECT

public:

    explicit ProjectWizard(Project *project = Q_NULLPTR, QWidget *parent = nullptr);

    ~ProjectWizard();

private:

    Ui::ProjectWizard   *ui;

    Project             *project;

private slots:

    void slotCancel();
};

#endif // PROJECT_WIZARD_H
