#ifndef MAINWINDOWSETTINGS_H
#define MAINWINDOWSETTINGS_H

#include <QWidget>

namespace Ui {
class MainWindowSettings;
}

class MainWindowSettings : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowSettings(int pluginCount, QWidget *parent = nullptr);
    ~MainWindowSettings();
signals:
    void gridChanged(int , int);

private slots:
    void handleSaveSettings();
    void handleRowComboBoxChanged(const QString &arg1);
    void handleColumnComboBoxChanged(const QString &arg1);

private:
    void initComboBox();
    int _pluginCount = 0;
    Ui::MainWindowSettings *ui;
};

#endif // MAINWINDOWSETTINGS_H
