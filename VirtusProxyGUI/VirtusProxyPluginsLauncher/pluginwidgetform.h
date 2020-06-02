#ifndef PLUGINWIDGETFORM_H
#define PLUGINWIDGETFORM_H

#include <QWidget>
class PluginIFace;
class SettingsWidget;
namespace Ui {
class PluginWidgetForm;
}

class PluginWidgetForm : public QWidget
{
    Q_OBJECT
public:
    explicit PluginWidgetForm(PluginIFace* plugin, QWidget *parent = nullptr);
    ~PluginWidgetForm();
    void paintEvent(QPaintEvent * e);
private slots:
    void handleStart();
    void initIFaces();
    void handleOnLogsClicked();

    void handleOnSettingsClicked();

private:
    PluginIFace* _plugin = nullptr;
    Ui::PluginWidgetForm *ui;
};

#endif // PLUGINWIDGETFORM_H
