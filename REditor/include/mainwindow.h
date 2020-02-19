#ifndef     MAINWINDOW_H
#define     MAINWINDOW_H

#include    <QMainWindow>

class Project;

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

private slots:

    void slotCreateNewRoute();

    void slotLoadRouteProject();

    void slotSaveRouteProject();

    void slotRoutePropertiesChanged();

    void slotApplyRouteProperties();
};

#endif // MAINWINDOW_H
