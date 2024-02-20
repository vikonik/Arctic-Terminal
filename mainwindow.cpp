#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qcustomplot.h"
#include "mainwindow.h"
#include "plot.h"
#include <QMessageBox>
#include <QSerialPort>

#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new Serial;
    m_status = new QLabel(this);
    statusBar()->addWidget(m_status);
    //ui->statusBar->addWidget(m_status);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);

connect(ui->actionConfigure, &QAction::triggered, serial->m_settings, &SettingsDialog::show);
connect(ui->actionConnect, &QAction::triggered, serial, &Serial::openSerialPort);
connect(ui->actionDisconnect, &QAction::triggered, serial, &Serial::closeSerialPort);

connect(serial, &Serial::portConnected, this, &MainWindow::checkConnection);
connect(serial, &Serial::portDisconnected, this, &MainWindow::checkDisconnection);


//    initActionsConnections();
//    connect(serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
//    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));



    QString name = "AI1";
    plotAI1 = new Plot(&name,1,50,-5,80);
    name.clear();
    name.append("AI2");
    plotAI2 = new Plot(&name,1,10,-25,80);
    name.clear();
    name.append("UI1");
    plotUI1 = new Plot(&name,1,9,-25,80);
    ui->layoutPlotAI1->addWidget(plotAI1);
    ui->layoutPlotAI1->addWidget(plotAI2);
    ui->layoutPlotAI1->addWidget(plotUI1);



    for(int i = 0; i < 80; i++){
        plotAI1->printTestGraph(i);
        plotAI2->printTestGraph(i*2);
        plotUI1->printTestGraph(i/2);
    }


    showStatusMessage("Load");



}

MainWindow::~MainWindow()
{
    delete ui;
}

/**/
void MainWindow::checkConnection(){

    const SettingsDialog::Settings p = serial->m_settings->settings();
    if (serial->port->isOpen()) {
                ui->actionConnect->setEnabled(false);
                ui->actionDisconnect->setEnabled(true);
                ui->actionConfigure->setEnabled(false);
                showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                  .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                  .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->port->errorString());

        showStatusMessage(tr("Open error"));
    }
}

/**/
void MainWindow::checkDisconnection(){
    if (serial->port->isOpen())
        serial->port->close();

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));

}


void MainWindow::initActionsConnections()
{
//    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
//    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    //connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    //connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
    //connect(m_ui->actionClear, &QAction::triggered, m_console, &Console::clear);
    //connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    //connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);

 //   connect(ui->actionConfigure,&QAction::triggered, serial, SLOT(sh));
}



/**/
void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
    //statusBar()->showMessage(message);
}


void MainWindow::on_pushButton_clicked()
{
    QByteArray data;
    data.append("qwe");
    serial->writeData(data);
    //ui->log->insertPlainText(data);
  //m_settings->show();
}
