#include    "project-wizard.h"
#include    "ui_projectwizard.h"

#include    "project.h"

#include    <QFileDialog>
#include    <QMessageBox>
#include    <QDir>

#include    "CfgEditor.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ProjectWizard::ProjectWizard(Project *project, QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::ProjectWizard)
  , project(project)  
{
    ui->setupUi(this);

    connect(ui->pbBrowse, &QPushButton::clicked, this, &ProjectWizard::slotBrowse);

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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::createProjectFile(QString file_name)
{
    if (project == Q_NULLPTR)
        return;

    CfgEditor editor;

    editor.openFileForWrite(project->getProjectDir() + QDir::separator() + file_name + ".xml");

    FieldsDataList flist;
    flist.append(QPair<QString, QString>("Title", ui->leRouteTitle->text()));
    flist.append(QPair<QString, QString>("DescriptionFile", "description"));
    editor.writeFile("Route", flist);

    editor.closeFileAfterWrite();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotBrowse()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open routes dir"),
                                                     QString(),
                                                     QFileDialog::ShowDirsOnly |
                                                     QFileDialog::DontResolveSymlinks);

    ui->leProjDirectory->setText(path);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotCreate()
{
    if (project == Q_NULLPTR)
        return;

    if (ui->leProjectName->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Empty name of project"));
        return;
    }

    if (ui->leProjDirectory->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Choose directory\nfor project location"));
        return;
    }

    QString project_dir = ui->leProjDirectory->text() + QDir::separator() + ui->leProjectName->text();
    QDir dir(project_dir);

    if (!dir.exists())
    {
        dir.mkdir(project_dir);
    }

    project->setProjectDir(project_dir);
    project->setTitle(ui->leRouteTitle->text());
    project->setName(ui->leProjectName->text());

    createProjectFile(ui->leProjectName->text());

    this->close();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotCancel()
{
    this->close();
}
