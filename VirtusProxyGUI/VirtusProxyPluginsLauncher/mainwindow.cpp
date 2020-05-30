#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pluginwidgetform.h"
#include "mainwindowsettings.h"
#include "settingsitem.h"

#include <QFileDialog>
#include <QLibrary>
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QSharedPointer>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit(tr("Виртус Прокси").toLocal8Bit().data()));
    _mnuBar  = new QMenuBar;
    _pmnu = new QMenu();
    _pmnu->setTitle(QString::fromLocal8Bit(tr("Меню").toLocal8Bit().data()));
    _pmnu->setVisible(true);
    _pmnu->addSeparator();
    _pmnu->addAction("&"+QString::fromLocal8Bit(tr("Настройки").toLocal8Bit().data()),this, &MainWindow::handleSettings,Qt::CTRL + Qt::Key_Q);
    _pmnu->addSeparator();
    _pmnu->addAction("&"+QString::fromLocal8Bit(tr("Загрузить новый плагин").toLocal8Bit().data()), this, &MainWindow::handleLoadNewPlugin);
    _mnuBar->addMenu(_pmnu);
    setMenuBar(_mnuBar);
    this->ui->centralwidget->setLayout(&_widgetsLayout);
    setUpPlugins();
    scroll.setWidget(this->ui->centralwidget);
    scroll.setWidgetResizable(true);
    setCentralWidget(&scroll);
}

void MainWindow::handleSettings()
{
    _settings = (new MainWindowSettings(_widgetsLayout.count()));
    QObject::connect(_settings, &MainWindowSettings::gridChanged, this, &MainWindow::handleGridChanged);
    _settings->show();
}

void MainWindow::setUpPlugins()
{
    QDir dir;
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    dir.cd("buildPlugins");
    dir.cd("debug");
    dir.cd("bin");
#ifdef Q_OS_UNIX
    QString extension("so");
#else
    QString extension("dll");
#endif
    foreach (auto finfo , dir.entryInfoList())
    {
        if (finfo.suffix() == extension)
        {
            loadNewPlugin(finfo.absoluteFilePath());
            loadNewPlugin(finfo.absoluteFilePath());
            loadNewPlugin(finfo.absoluteFilePath());
            loadNewPlugin(finfo.absoluteFilePath());
        }
    }
}

void MainWindow::loadNewPlugin(QString path)
{
    if(!QFileInfo::exists(path))
    {
        return;
    }
    qDebug() << "Try load" << path;
    QLibrary lib;
    if(QLibrary::isLibrary(path))
    {
        lib.setFileName(path);
        lib.load();
        if(lib.isLoaded())
        {
            qDebug() << "Ok";
        }
        else
        {
            qDebug() << "Error " << lib.errorString();
        }
    }
    else
    {
        qDebug() << "Not a library";
        return;
    }

    typedef PluginIFace *(*createPlugin)();
    createPlugin cwf = (createPlugin)lib.resolve("create");
//    typedef void (*deletePlugin)(PluginIFace*);
//    deletePlugin qwe = (deletePlugin)lib.resolve("deletePlugin");
    if (cwf)
    {
        PluginIFace *plugin = cwf();
        if (plugin)
        {
            PluginWidgetForm *pw = new PluginWidgetForm(plugin);
            pluginList.push_back(pw);
            this->ui->centralwidget->layout()->addWidget(pw);
        }
    }
    else
    {
        qDebug() << "Could not show widget from the loaded library";
    }
}

void MainWindow::handleGridChanged(int rows, int columns)
{
    int k = 0;
    for (int i = 0;i<_widgetsLayout.rowCount();i++)
    {
        for(int j = 0;j<_widgetsLayout.columnCount();j++)
        {
            _widgetsLayout.removeItem(_widgetsLayout.itemAtPosition(i, j));
        }
    }
    for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<columns; j++)
        {
            if(k==pluginList.size())
            {
                return;
            }
            _widgetsLayout.addWidget(pluginList.at(k), i, j);
            k++;
        }
    }
    update();
}

void MainWindow::handleLoadNewPlugin()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit(tr("Загрузить плагин").toLocal8Bit().data()), QString(),
                                                    tr("Files (*.dll *.so)"));
    loadNewPlugin(fileName);
    handleGridChanged(_widgetsLayout.rowCount(), _widgetsLayout.columnCount());
}

MainWindow::~MainWindow()
{
    delete ui;
}

