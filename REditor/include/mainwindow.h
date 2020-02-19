#ifndef     MAINWINDOW_H
#define     MAINWINDOW_H

#include    <QMainWindow>

class Project;

class QTableWidget;

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace Ui
{
    class MainWindow;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:

    Ui::MainWindow  *ui;

    Project         *current_project;

    void enablePropertiesButtons();

    void disablePropertiesButtons();

    bool checkUnsavedChanges();

    void closeEvent(QCloseEvent *event);

    void updateProjectTree();

    void updateProfileData(QTableWidget *tw);

private slots:

    void slotCreateNewRoute();

    void slotLoadRouteProject();

    void slotSaveRouteProject();

    void slotRoutePropertiesChanged();

    void slotApplyRouteProperties();

    void slotAddProfElementBefore();

    void slotAddProfElementAfter();

    void slotRemoveProfElement();

    void slotProfileChanged(int row, int column);
};

#endif // MAINWINDOW_H
