#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindowSettings;
class PluginWidgetForm;
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLibrary>
#include <QScrollArea>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 *  class-widget displaying the main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void setUpPlugins();
    void loadNewPlugin(QString path);
    QGridLayout _widgetsLayout;
    QWidget central;
    QMenuBar* _mnuBar;
    QMenu* _pmnu;
    MainWindowSettings* _settings;
    QList<PluginWidgetForm*> pluginList;
    Ui::MainWindow *ui;
    QScrollArea scroll;
private slots:
    void handleSettings(); ///<???? ?? ???????? ???? ? ??????????? ???????
    void handleLoadNewPlugin(); ///<???? ?? ???????? ???? ? ??? ???????? ?????? ???????
    void handleGridChanged(int rows, int columns);
};
#endif // MAINWINDOW_H
