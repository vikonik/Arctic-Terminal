#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "qcustomplot.h"
#include <QVector>
#include "plot.h"
#include "serial.h"
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>
//#include "settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SettingsDialog;
//class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initActionsConnections();
    void showStatusMessage(const QString &message);

    void printGraph(QList<QString> lst);
    void printStatus(QList<QString> lst);

    void writeTmpFile(QList<QString> lst);
    void openTmpFile();
    void writeToLog(QString *str);
public slots:
    void checkConnection();
    void checkDisconnection();
    void parseTemp(QByteArray data);

    void clearAllGrapf();
private slots:


    void on_pushButton_loadAll_clicked();

private:
    Ui::MainWindow *ui;
SettingsDialog *m_settings;
    Serial *serial = nullptr;
    QLabel *m_status = nullptr;
    QStatusBar *m_statusBar = nullptr;
Plot *plotAI1;
Plot *plotAI2;
Plot *plotUI1;

QString *pathFile;
QFile *file;

QString *pathFileTmp;
QFile *fileTmp;

    QVector<double> x,y;
    enum{
        KEY_DATA,
        WORK_TEMPERATURE,
        AI1,
        AI2,
        UI1,
        SPI
    }Temperature_e;
};
#endif // MAINWINDOW_H
