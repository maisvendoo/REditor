#include    "project-wizard.h"
#include    "ui_project-wizard.h"

#include    "project.h"
#include    "CfgEditor.h"

#include    <QMessageBox>
#include    <QDir>
#include    <QFile>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectWizard::ProjectWizard(Project *project, QWidget *parent) : QDialog(parent)
  , ui(new Ui::ProjectWizard)
  , project(project)
{
    ui->setupUi(this);

    connect(ui->pbBrowse, &QPushButton::clicked, this, &ProjectWizard::slotBrowse);
    connect(ui->pbCreateRoute, &QPushButton::clicked, this, &ProjectWizard::slotCreateRoute);
    connect(ui->pbCancel, &QPushButton::clicked, this, &ProjectWizard::slotCancel);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectWizard::~ProjectWizard()
{
    delete ui;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::createProjectFiles()
{
    QString name = ui->leProjectName->text();
    QString project_dir = ui->leProjectsDir->text() + QDir::separator() + name;
    QString title = ui->leRouteTitle->text();

    project->setName(name);
    project->setTitle(title);
    project->setProjectDir(project_dir);

    QDir dir(project_dir);

    if (!dir.exists())
    {
        dir.mkdir(project_dir);
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotBrowse()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotCreateRoute()
{
    if (ui->leProjectName->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please, set project's name"));
        return;
    }

    if (ui->leProjectsDir->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please, set project placement"));
        return;
    }
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotCancel()
{
    this->close();
}
