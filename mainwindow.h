#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "qcustomplot.h"
#include <QVector>
#include "plot.h"
#include "serial.h"
#include <QLabel>
#include <QStatusBar>

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

public slots:
    void checkConnection();


    void checkDisconnection();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
SettingsDialog *m_settings;
    Serial *serial = nullptr;
    QLabel *m_status = nullptr;
    QStatusBar *m_statusBar = nullptr;
Plot *plotAI1;
Plot *plotAI2;
Plot *plotUI1;


    QVector<double> x,y;
};
#endif // MAINWINDOW_H
