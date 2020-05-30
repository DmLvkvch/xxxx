#include "mainwindowsettingsgrid.h"

#include <QLabel>
#include <QVBoxLayout>

MainWindowSettingsGrid::MainWindowSettingsGrid(QWidget* parent):QWidget(parent)
{
    QLabel *grid = new QLabel(tr("Choose grid"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(grid);
    setLayout(mainLayout);
}

MainWindowSettingsGrid::~MainWindowSettingsGrid()
{

}
