#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class Setting;
}
class SettingsItem;
class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(SettingsItem setting, QWidget *parent = nullptr);
    ~Setting();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
