#ifndef MAINWINDOWSETTINGSGRID_H
#define MAINWINDOWSETTINGSGRID_H

#include <QWidget>


/*!
 *  class-widget displaying settings with grid layout
 */
class MainWindowSettingsGrid: public QWidget
{
    Q_OBJECT
public:
    MainWindowSettingsGrid(QWidget* parent = nullptr);
    ~MainWindowSettingsGrid();
};

#endif // MAINWINDOWSETTINGSGRID_H
