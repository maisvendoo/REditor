#include    "project-wizard.h"
#include    "ui_project-wizard.h"

#include    "project.h"
#include    "CfgEditor.h"

#include    <QMessageBox>
#include    <QDir>
#include    <QFile>
#include    <QFileDialog>

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

    CfgEditor editor;

    editor.openFileForWrite(project_dir + QDir::separator() + name + ".xml");
    FieldsDataList flist;
    flist.append(QPair<QString, QString>("Title", title));
    flist.append(QPair<QString, QString>("Description", "description"));
    editor.writeFile("Route", flist);
    editor.closeFileAfterWrite();

    createEmptyFile("profile");
    createEmptyFile("description");

    QFile route_type(project_dir + QDir::separator() + "route-type");
    route_type.open(QIODevice::WriteOnly);
    route_type.write(QString("rrs").toStdString().c_str());
    route_type.close();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::createEmptyFile(QString file_name)
{
    QFile prof_file(project->getProjectDir() + QDir::separator() + file_name);
    prof_file.open(QIODevice::WriteOnly);
    prof_file.close();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotBrowse()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("Open project's directory"),
                                                     QString(),
                                                     QFileDialog::ShowDirsOnly |
                                                     QFileDialog::DontResolveSymlinks);

    ui->leProjectsDir->setText(path);
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

    createProjectFiles();

    this->close();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void ProjectWizard::slotCancel()
{
    this->close();
}
