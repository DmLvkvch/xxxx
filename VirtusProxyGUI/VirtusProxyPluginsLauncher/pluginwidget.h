#ifndef PluginWidget_H
#define PluginWidget_H

class PluginIFace;
class SettingsWidget;
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

/*!
 *  class-widget displaying plugin
 */
class PluginWidget : public QWidget
{
    Q_OBJECT

public:
    PluginWidget(PluginIFace* plugin, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);///<метод для отображения виджета
    virtual  ~PluginWidget();
private slots:
    void handleOpenLogs();
    void handleOpenSettings();
    void handleStart();
    void initIFaces();
private:
    QGridLayout _grid;
    PluginIFace* _plugin;
    QString _widgetName;
    QSharedPointer<QWidget> _parentCustomWidget;
    QPushButton _openLogsButton;
    QPushButton _openSettingsButton;
    QSharedPointer<SettingsWidget> _settings;
};

#endif // PluginWidget_H
