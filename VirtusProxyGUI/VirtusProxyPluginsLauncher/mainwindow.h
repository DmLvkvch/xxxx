#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindowSettings;
class PluginWidgetForm;
class PluginIFace;
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLibrary>
#include <QScrollArea>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

typedef PluginIFace *(*createPlugin)();
typedef void (*deletePlugin)(PluginIFace*);

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
    QGridLayout* _widgetsLayout;
    QWidget* _central;
    QMenuBar* _mnuBar = nullptr;
    QMenu* _pmnu = nullptr;
    MainWindowSettings* _settings = nullptr;
    QList<PluginWidgetForm*> pluginList;
    Ui::MainWindow *ui;
    QScrollArea* _scroll;
    QList<QPair<deletePlugin, PluginIFace*>> plugins;
private slots:
    void handleSettings(); ///<настройки главного окна
    void handleLoadNewPlugin(); ///<загрузка нового плагина
    void handleGridChanged(int rows, int columns);///<изменения сетки
};
#endif // MAINWINDOW_H
