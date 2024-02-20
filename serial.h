#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QSerialPort>
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

public slots:
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void writeData(const QByteArray &data);
    void readData();

private:



};

#endif // SERIAL_H
