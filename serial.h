#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
//#include "settingsdialog.h"

class SettingsDialog;

class Serial : public QWidget
{
    Q_OBJECT
public:
    explicit Serial(QWidget *parent = nullptr);
SettingsDialog *m_settings = nullptr;
QSerialPort *port = nullptr;

signals:
    void portConnected();
    void portDisconnected();
    void signalRcvData(QByteArray);//Сигнал при получении данных

public slots:
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void dataWrite(const QByteArray &data);
    void readData();

    void checkRCVData();
private:



};

#endif // SERIAL_H
