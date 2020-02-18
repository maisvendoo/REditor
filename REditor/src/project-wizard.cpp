#include    "project-wizard.h"
#include    "ui_project-wizard.h"

#include    "project.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectWizard::ProjectWizard(Project *project, QWidget *parent) : QDialog(parent)
  , ui(new Ui::ProjectWizard)
  , project(project)
{
    ui->setupUi(this);

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
void ProjectWizard::slotCancel()
{
    this->close();
}
