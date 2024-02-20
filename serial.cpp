#include "serial.h"
#include <QMessageBox>
#include "settingsdialog.h"
#include <QtDebug>
#include <QObject>

Serial::Serial(QWidget *parent) : QWidget(parent)
{
    m_settings = new SettingsDialog;
    port = new QSerialPort;
    connect(port, &QSerialPort::readyRead, this, &Serial::readData);

}


/**/
void Serial::openSerialPort()
{
qDebug("openSerialPort");
    const SettingsDialog::Settings p = m_settings->settings();
    port->setPortName(p.name);
    bool ok = port->open(QIODevice::ReadWrite);
    ok &= port->setBaudRate(p.baudRate);
    ok &= port->setDataBits(p.dataBits);
    ok &= port->setParity(p.parity);
    ok &= port->setStopBits(p.stopBits);
    ok &= port->setFlowControl(p.flowControl);


    qDebug() << port->portName() << (ok ? "opened" : "NOT opened");
    emit portConnected();

}
//! [4]

/**/
void Serial::closeSerialPort()
{
    qDebug("closeSerialPort");
    emit portDisconnected();

    if (port->isOpen())
        port->close();
    emit portDisconnected();    //    m_console->setEnabled(false);

}

/**/
void Serial::handleError(QSerialPort::SerialPortError error)
{
//    if (error == QSerialPort::ResourceError) {
//        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
//        closeSerialPort();
//    }
}

/**/
void Serial::writeData(const QByteArray &data)
{
    if(port->isOpen()){
        qDebug("Send data ");
        port->write(data);
        qDebug()<<port->portName();
        qDebug()<<port->baudRate();
        qDebug()<<port->dataBits();
        qDebug()<<port->parity();
        qDebug()<<port->stopBits();
    }
    else
        qDebug("Port CLOSED");

qDebug()<<port->bytesToWrite();
}

/**/
void Serial::readData()
{
    const QByteArray data = port->readAll();
    qDebug() << tr("Recive bytes ");
    qDebug() << tr("Recive bytes %1").arg(data.size());
    qDebug()<< data.data();
}
