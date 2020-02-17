#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QAction>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew_route, &QAction::triggered, this, &MainWindow::slotCreateNewRoute);
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
void MainWindow::slotCreateNewRoute()
{

}
