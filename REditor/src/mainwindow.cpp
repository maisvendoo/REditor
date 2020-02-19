#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QAction>
#include    <QLineEdit>
#include    <QPlainTextEdit>
#include    <QPushButton>
#include    <QTreeWidget>
#include    <QTreeWidgetItem>
#include    <QTableWidget>
#include    <QTableWidgetItem>

#include    <QMessageBox>
#include    <QDir>
#include    <QFileInfo>
#include    <QFileDialog>

#include    "project.h"
#include    "project-wizard.h"
#include    "profile.h"

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

    connect(ui->pbProfPrevElementAdd, &QPushButton::clicked, this, &MainWindow::slotAddProfElementBefore);
    connect(ui->pbProfNextElementAdd, &QPushButton::clicked, this, &MainWindow::slotAddProfElementAfter);
    connect(ui->pbProfElementRemove, &QPushButton::clicked, this, &MainWindow::slotRemoveProfElement);

    connect(ui->twProfileData, &QTableWidget::cellChanged, this, &MainWindow::slotProfileChanged);

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
void MainWindow::updateProjectTree()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::updateProfileData(QTableWidget *tw)
{
    if (current_project == Q_NULLPTR)
        return;

    Profile *profile = current_project->getProfile();

    if (profile == Q_NULLPTR)
        return;

    profile->setInitOrdinate(ui->sbInitOrdinate->value());
    profile_container_t elements = profile->getElements();

    tw->setRowCount(0);

    for (int j = 0; j < elements.size(); ++j)
    {
        tw->insertRow(j);
        tw->setRowHeight(j, 20);

        profile_element_t *e = elements.at(j);

        if (j == 0)
        {
            e->linear_coordinate = 0;
            e->ordinate = ui->sbInitOrdinate->value();
        }
        else
        {
            e->linear_coordinate = elements.at(j - 1)->linear_coordinate +
                                   elements.at(j - 1)->length;

            e->ordinate = elements.at(j - 1)->ordinate + elements.at(j - 1)->length;
        }

        QTableWidgetItem *lin_coord_item = new QTableWidgetItem;
        lin_coord_item->setText(QString("%1").arg(e->linear_coordinate, 10, 'f', 1));
        lin_coord_item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tw->setItem(j, 0, lin_coord_item);

        QTableWidgetItem *ordinate_item = new QTableWidgetItem;
        ordinate_item->setText(QString("%1").arg(e->ordinate, 10, 'f', 1));
        ordinate_item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tw->setItem(j, 1, ordinate_item);

        QTableWidgetItem *length_item = new QTableWidgetItem;
        length_item->setText(QString("%1").arg(e->length, 7, 'f', 1));
        length_item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tw->setItem(j, 2, length_item);

        QTableWidgetItem *inclination_item = new QTableWidgetItem;
        inclination_item->setText(QString("%1").arg(e->inclination, 5, 'f', 1));
        inclination_item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tw->setItem(j, 3, inclination_item);

        QTableWidgetItem *radius_item = new QTableWidgetItem;
        radius_item->setText(QString("%1").arg(e->radius, 8));
        radius_item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tw->setItem(j, 4, radius_item);
    }
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

    updateProjectTree();
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotAddProfElementBefore()
{
    if (current_project == Q_NULLPTR)
        return;

    Profile *profile = current_project->getProfile();

    if (profile == Q_NULLPTR)
        return;

    int row = ui->twProfileData->currentRow();

    profile_element_t *e = new profile_element_t();
    profile->insert_after(row, e);

    updateProfileData(ui->twProfileData);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotAddProfElementAfter()
{
    if (current_project == Q_NULLPTR)
        return;

    Profile *profile = current_project->getProfile();

    if (profile == Q_NULLPTR)
        return;

    int row = ui->twProfileData->currentRow();

    profile_element_t *e = new profile_element_t();
    profile->insert_after(row, e);

    updateProfileData(ui->twProfileData);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotRemoveProfElement()
{
    if (current_project == Q_NULLPTR)
        return;

    Profile *profile = current_project->getProfile();

    if (profile == Q_NULLPTR)
        return;

    int row = ui->twProfileData->currentRow();

    profile->remove(row);

    updateProfileData(ui->twProfileData);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotProfileChanged(int row, int column)
{
    if (current_project == Q_NULLPTR)
        return;

    Profile *profile = current_project->getProfile();

    if (profile == Q_NULLPTR)
        return;

    profile_element_t *e = profile->getElements().at(row);

    double value = ui->twProfileData->item(row, column)->text().toDouble();

    switch (column)
    {
    case 2:

        e->length = value;
        break;

    case 3:

        e->inclination = value;
        break;

    case 4:

        e->radius = static_cast<qint32>(value);
        break;
    }
}

