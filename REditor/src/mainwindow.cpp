#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QAction>
#include    <QLineEdit>
#include    <QPlainTextEdit>
#include    <QPushButton>
#include    <QTreeWidget>
#include    <QTreeWidgetItem>

#include    <QMessageBox>
#include    <QDir>
#include    <QFileInfo>
#include    <QFileDialog>

#include    "project.h"
#include    "project-wizard.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , current_project(Q_NULLPTR)
{
    ui->setupUi(this);

    connect(ui->actionNew_route, &QAction::triggered, this, &MainWindow::slotCreateNewRoute);
    connect(ui->actionOpen_route, &QAction::triggered, this, &MainWindow::slotLoadRouteProject);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::slotSaveRouteProject);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->leRouteTitle, &QLineEdit::textChanged, this, &MainWindow::slotRoutePropertiesChanged);
    connect(ui->ptRouteDescription, &QPlainTextEdit::textChanged, this, &MainWindow::slotRoutePropertiesChanged);

    connect(ui->pbPropApply, &QPushButton::clicked, this, &MainWindow::slotApplyRouteProperties);
    connect(ui->pbPropCancel, &QPushButton::clicked, ui->leRouteTitle, &QLineEdit::undo);
    connect(ui->pbPropCancel, &QPushButton::clicked, ui->ptRouteDescription, &QPlainTextEdit::undo);

    ui->twProfileData->horizontalHeader()->setStretchLastSection(true);
    ui->twProfileData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twProfileData->setRowCount(0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::enablePropertiesButtons()
{
    ui->pbPropApply->setEnabled(true);
    ui->pbPropCancel->setEnabled(true);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::disablePropertiesButtons()
{
    ui->pbPropApply->setEnabled(false);
    ui->pbPropCancel->setEnabled(false);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool MainWindow::checkUnsavedChanges()
{
    if (current_project == Q_NULLPTR)
        return true;

    if (current_project->isChanged())
    {
        int button = QMessageBox::warning(this, tr("Warning"),
                                        tr("Current route is modified.\n Do you want to save it?"),
                                        tr("Yes"), tr("No"), tr("Cancel"), 0, 2);

        switch (button)
        {
        case 0:

            current_project->save();
            return true;

        case 1:

            return true;

        case 2:

            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (checkUnsavedChanges())
        event->accept();
    else
        event->ignore();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::initProjectFilesystem(QString path)
{
    QFileInfo   info(path);

    current_project->setName(info.baseName());
    current_project->setProjectDir(info.path());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::updateProjectTree()
{
    ui->treeProject->clear();

    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, current_project->getName());
    ui->treeProject->addTopLevelItem(item);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotCreateNewRoute()
{
    if (!checkUnsavedChanges())
        return;

    if (current_project != Q_NULLPTR)
    {
        delete current_project;
        current_project = Q_NULLPTR;
    }

    current_project = new Project();

    ProjectWizard *wizard = new ProjectWizard(current_project, this);
    wizard->exec();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotLoadRouteProject()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotSaveRouteProject()
{
    if (current_project != Q_NULLPTR)
        current_project->save();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotRoutePropertiesChanged()
{
    if (current_project == Q_NULLPTR)
        return;

    enablePropertiesButtons();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotApplyRouteProperties()
{
    if (current_project == Q_NULLPTR)
        return;

    current_project->setTitle(ui->leRouteTitle->text());
    current_project->setTitle(ui->ptRouteDescription->toPlainText());

    disablePropertiesButtons();
}

