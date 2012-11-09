#include "AdminWindow.h"
#include "ui_AdminWindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::AdminWindow) {
    ui->setupUi(this);
    qApp->setApplicationName("admin");
    qApp->setApplicationVersion("1.0.1a");
    ui->mainToolBar->addAction(ui->actionSave);
    queryBean = NULL;
    currentPanel = NULL;
    try   {
        initialize();
    }
    catch( const QString& exception) {
        qDebug() << exception;
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
    ui->appIconLabel->setPixmap(QIcon("./images/admin_icon.png").pixmap(QSize(64,64)));

    connect(ui->btDeviceAdmin, SIGNAL(clicked()), this, SLOT(OnBtDeviceAdminClick()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionNewDevice, SIGNAL(triggered()), this, SLOT(OnNewDeviceTriggered()));
}

AdminWindow::~AdminWindow() {
    delete ui;
    delete queryBean;
    if(currentPanel) delete currentPanel;
}

void AdminWindow::OnBtDeviceAdminClick() {
    DeviceAdministrationPanel* panel = new DeviceAdministrationPanel(&moduleList, queryBean);
    panel->setAttribute(Qt::WA_DeleteOnClose);
    if(currentPanel) delete currentPanel;
    currentPanel = panel;
    ui->centralLayout->addWidget(panel);
}

void AdminWindow::initialize() {
    qDebug() << "init";
    DatabaseConnectionDialog connectionDialog;
    QObject::connect(&connectionDialog, SIGNAL(propertiesValidated(DatabaseProperties*)), this, SLOT(connectDatabase(DatabaseProperties*)));
    connectionDialog.setVisible(true);
    //cause double delete pointer
    //connectionDialog.setAttribute(Qt::WA_DeleteOnClose);
    connectionDialog.exec();
}

void AdminWindow::OnNewDeviceTriggered() {
    DeviceCreationDialog *dialog = new DeviceCreationDialog(&moduleList, queryBean, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void AdminWindow::OnNewModuleTriggered() {

}

void AdminWindow::connectDatabase(DatabaseProperties* databaseProperties) {
    try {
        if(!databaseProperties)
            throw error::NullPointerException("databaseProperties null pointer !", AT);
        DatabaseProperties p = *databaseProperties;
        delete databaseProperties;
        queryBean = new QueryBean(p);
        moduleList = queryBean->buildModuleList();
    }
    catch(const error::NullPointerException& exception) {
        qDebug() << exception.toString();
    }
}
