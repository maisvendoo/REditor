#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QAction>
#include    <QLineEdit>
#include    <QPlainTextEdit>
#include    <QPushButton>

#include    "project.h"

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

    connect(ui->leRouteTitle, &QLineEdit::textChanged, this, &MainWindow::slotRoutePropertiesChanged);
    connect(ui->ptRouteDescription, &QPlainTextEdit::textChanged, this, &MainWindow::slotRoutePropertiesChanged);

    connect(ui->pbPropApply, &QPushButton::clicked, this, &MainWindow::slotApplyRouteProperties);
    connect(ui->pbPropCancel, &QPushButton::clicked, ui->leRouteTitle, &QLineEdit::undo);
    connect(ui->pbPropCancel, &QPushButton::clicked, ui->ptRouteDescription, &QPlainTextEdit::undo);
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
void MainWindow::slotCreateNewRoute()
{

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

