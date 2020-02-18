#include    "project-wizard.h"
#include    "ui_projectwizard.h"

#include    "project.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectWizard::ProjectWizard(Project *project, QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::ProjectWizard)
  , project(project)
{
    ui->setupUi(this);

    connect(ui->pbCancel, &QPushButton::clicked, this, &ProjectWizard::slotCancel);
    connect(ui->pbCreateRoute, &QPushButton::clicked, this, &ProjectWizard::slotCreate);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectWizard::~ProjectWizard()
{
    delete ui;
}

void ProjectWizard::slotCreate()
{

}

void ProjectWizard::slotCancel()
{
    close();
}
