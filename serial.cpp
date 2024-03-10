#include "serial.h"
#include <QMessageBox>
#include "settingsdialog.h"
#include <QtDebug>
#include <QObject>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QObject>

Serial::Serial(QWidget *parent) : QWidget(parent)
{
    m_settings = new SettingsDialog;
    port = new QSerialPort(this);
//    connect(port, &QSerialPort::errorOccurred, this, SLOT(handleError()));
    connect(port, &QSerialPort::errorOccurred, this, &Serial::handleError);
//    QObject::connect(port, &QSerialPort::readyRead, this, &Serial::readData);

    //connect(port, SIGNAL(readData()), this, SLOT(readData()));
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(readData()));

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
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), port->errorString());
        closeSerialPort();
    }
}


/**/
void Serial::dataWrite(const QByteArray &data)
{

    if(port->isOpen()){
        qDebug("Send data ");
        port->write(data);
/*        if(port->isWritable())
            qDebug()<< "Thrue";
        else
            qDebug()<<"False";

        qDebug()<<port->portName();
        qDebug()<<port->baudRate();
        qDebug()<<port->dataBits();
        qDebug()<<port->parity();
        qDebug()<<port->stopBits();

        if(!port->waitForBytesWritten(10)){
            qDebug()<<"Команда исключения "<<port->errorString();
            port->clearError();
        }
*/
    }
    else
        qDebug("Port CLOSED");

qDebug()<<port->bytesToWrite();
//qDebug()<<"Команда исключения "<<port->errorString();
}

/**/
void Serial::readData()
{
    qint64 a = port->bytesAvailable();
    if (a == 0)//Обработка ложного срабатывания
        return;
    qDebug() << tr("Try to Recive bytes ");
    QByteArray data = port->readAll();
    qDebug() << tr("Recive bytes ");
    //qDebug() << tr("Recive bytes %1").arg(a);
    qDebug()<< data.data();
    qDebug()<< tr("Recive bytes %1").arg(data.data());
    emit signalRcvData(data);
}

/**/
void Serial::checkRCVData(){
    qDebug()<<"checkRCVData";
    port->waitForReadyRead(10);
    qint64 a = port->bytesAvailable();
    if (a == 0)//Обработка ложного срабатывания
        return;

    qDebug()<< tr("recive %1 byte").arg(a);
    QByteArray data = port->readAll();
    qDebug()<< tr("Recive bytes %1").arg(data.data());
    emit signalRcvData(data);

}
