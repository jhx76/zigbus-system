#ifndef DEVICEEDITIONPANEL_H
#define DEVICEEDITIONPANEL_H

#include <QWidget>
#include <core/Device.h>


namespace Ui {
    class DeviceEditionPanel;
}

class DeviceEditionPanel : public QWidget
{
    Q_OBJECT
private:
    Ui::DeviceEditionPanel *ui;

    Device* deviceInEdition;

public:
    DeviceEditionPanel(QWidget *parent = 0);

    DeviceEditionPanel(Device *deviceToEdit, QWidget *parent = 0);

    ~DeviceEditionPanel();


public slots:
    void onSaveDevice();

signals:
    void um_save_device(Device*);


};

#endif // DEVICEEDITIONPANEL_H
