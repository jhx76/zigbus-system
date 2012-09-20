#include "AdminWindow.h"
#include "ui_AdminWindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::AdminWindow) {
    ui->setupUi(this);
    ui->mainToolBar->addAction(ui->actionSave);

    database = QSqlDatabase::addDatabase("QMYSQL");
    initialize();


    connect(ui->btDeviceAdmin, SIGNAL(clicked()), this, SLOT(OnBtDeviceAdminClick()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


}

AdminWindow::~AdminWindow() {

    delete ui;
}

void AdminWindow::OnBtDeviceAdminClick() {
    DeviceAdministrationPanel* panel = new DeviceAdministrationPanel(&moduleList);
    panel->setAttribute(Qt::WA_DeleteOnClose);
    ui->centralLayout->addWidget(panel);
}

void AdminWindow::initialize() {

    statusBar()->showMessage("initialize: database connection...");
    database.setHostName("localhost");
    database.setDatabaseName("zigbus-system");
    database.setUserName("root");
    database.setPassword("cherry");
    if(!database.open())
        throw QString("Cannot reach the database ! EXIT");
    statusBar()->showMessage("initialize: database connected !");

    statusBar()->showMessage("initialize: importing data");
    QSqlQuery query("SELECT t_module.moduleid AS label, "
                    "t_module.nbpin_numeric, "
                    "t_module.nbpin_analogic, "
                    "t_module.description, "
                    "t_zigbus_network.network_id "
                    "FROM t_module "
                    "INNER JOIN t_zigbus_network on t_module.et_zigbus_netid = t_zigbus_network.id");
    while(query.next()) {
        Module tmpModule;
        tmpModule.setNumericIOCount(query.value(query.record().indexOf("nbpin_numeric")).toInt());
        tmpModule.setAnalogIOCount(query.value(query.record().indexOf("nbpin_analogic")).toInt());
        tmpModule.setLabel(query.value(query.record().indexOf("label")).toString());
        tmpModule.setZigbusNetworkId(query.value(query.record().indexOf("network_id")).toString());
        moduleList.append(tmpModule);
    }

    for(int imod = 0; imod < moduleList.count(); imod++) {

        QString sqry =  "SELECT main_pin, optional_pin, t_hardware_type.label AS hardware_type, "
                        "t_symbolic_type.label AS symbolic_type, t_symbolic_network.label AS symbolic_network, "
                        "t_location.label AS location, instance "
                        "FROM t_device "
                        "INNER JOIN t_module ON t_device.et_module = t_module.id "
                        "INNER JOIN t_hardware_type ON t_device.et_hardware_type = t_hardware_type.id "
                        "INNER JOIN t_symbolic_type ON t_device.et_symbolic_type = t_symbolic_type.id "
                        "INNER JOIN t_symbolic_network ON t_device.et_symbolic_network = t_symbolic_network.id "
                        "INNER JOIN t_location ON t_device.et_location = t_location.id "
                        "INNER JOIN t_zigbus_network ON t_module.et_zigbus_netid = t_zigbus_network.id "
                        "WHERE t_zigbus_network.network_id ='"+moduleList[imod].getZigbusNetworkId()+"' "
                        "AND t_module.moduleid = '"+moduleList[imod].getLabel()+"'";
        QSqlQuery queryDevice(sqry);
        while(queryDevice.next()) {
            Device tmpDevice;
            tmpDevice.setVendor(queryDevice.value(queryDevice.record().indexOf("symbolic_network")).toString());
            tmpDevice.setType(queryDevice.value(queryDevice.record().indexOf("symbolic_type")).toString());
            tmpDevice.setLocation(queryDevice.value(queryDevice.record().indexOf("location")).toString());
            tmpDevice.setInstance(queryDevice.value(queryDevice.record().indexOf("instance")).toString());
            tmpDevice.setPinId(queryDevice.value(queryDevice.record().indexOf("main_pin")).toString());
            tmpDevice.setPinType(queryDevice.value(queryDevice.record().indexOf("hardware_type")).toString());
            tmpDevice.setPtrModule(&moduleList[imod]);
            moduleList[imod].append(tmpDevice);
        }
    }
}
