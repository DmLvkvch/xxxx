#ifndef CONNECTIONIFACEWIDGETFORM_H
#define CONNECTIONIFACEWIDGETFORM_H

#include <QWidget>
class ConnectionIFace;

namespace Ui {
class ConnectionIFaceWidgetForm;
}

class ConnectionIFaceWidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionIFaceWidgetForm(ConnectionIFace & iface, QWidget *parent = nullptr);
    ~ConnectionIFaceWidgetForm();
public slots:
    void connection();
    void msgIn();
    void msgOut();
private:
    void initIFace();
    ConnectionIFace & _iface;
    int _countIn = 0;
    int _countOut = 0;
    Ui::ConnectionIFaceWidgetForm *ui;
};

#endif // CONNECTIONIFACEWIDGETFORM_H
