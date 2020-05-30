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
    void on__save_clicked();

    void on__rowComboBox_currentIndexChanged(const QString &arg1);

    void on__columnComboBox_currentIndexChanged(const QString &arg1);

private:
    void initComboBox();
    int _pluginCount = 0;
    Ui::MainWindowSettings *ui;
};

#endif // MAINWINDOWSETTINGS_H
