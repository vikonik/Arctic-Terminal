/*
Версия QT 5.13.1 глючная, в ней не работает com порт
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qcustomplot.h"
#include "mainwindow.h"
#include "plot.h"
#include <QMessageBox>
#include <QSerialPort>
#include <QDebug>
#include "settingsdialog.h"
#include <QBitArray>
#include <QList>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>

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

    initActionsConnections();//весь connect вынесем в отдельный метод

    //Настроим графики для отображения
    QString name = "AI1";
    plotAI1 = new Plot(&name,1,50,-5,80);
    plotAI1->plotTestInit();
    name.clear();
    name.append("AI2");
    plotAI2 = new Plot(&name,1,10,-25,80);
    plotAI2->plotTestInit();
    name.clear();
    name.append("UI1");
    plotUI1 = new Plot(&name,1,9,-25,80);
    plotUI1->plotTestInit();
    ui->layoutPlotAI1->addWidget(plotAI1);
    ui->layoutPlotAI1->addWidget(plotAI2);
    ui->layoutPlotAI1->addWidget(plotUI1);


//Печатаем новую точку на графике
//    for(int i = 0; i < 80; i++){
//        plotAI1->printTestGraph(i);
//        plotAI2->printTestGraph(i*2);
//        plotUI1->printTestGraph(i/2);
//    }


    pathFile = new QString;
    file = new QFile;
    pathFileTmp = new QString;
    fileTmp = new QFile;
    openTmpFile();//Временный файл
/**/
    showStatusMessage("Load");


//QString str = "Temp 20.00 21.01 22.02 23.03";
//QList<QString> lst = str.split(' ');
//qDebug() << lst;
//qDebug() << lst.at(0);
//qDebug() << lst.at(1);
//qDebug() << lst.at(2);
//qDebug() << lst.at(3);
//qDebug() << lst.at(4);
    QString str = tr("Готов.");
    writeToLog(&str);
}

MainWindow::~MainWindow()
{
    delete ui;
    fileTmp->close();
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
    //Кнопка Настройка в меню
    connect(ui->actionConfigure, &QAction::triggered, serial->m_settings, &SettingsDialog::show);
    connect(ui->actionConfigure, &QAction::triggered, serial->m_settings, &SettingsDialog::fillPortsInfo);
    //Кнопки Попключит/Отключить в меню
    connect(ui->actionConnect, &QAction::triggered, serial, &Serial::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, serial, &Serial::closeSerialPort);

    //Изменение состояние порта вкл/откл
    connect(serial, &Serial::portConnected, this, &MainWindow::checkConnection);
    connect(serial, &Serial::portDisconnected, this, &MainWindow::checkDisconnection);

    //Сигнал приема данных для парсинга
    connect(serial,SIGNAL(signalRcvData(QByteArray)), this, SLOT(parseTemp(QByteArray)));

    //Кнопка Очистить всё
        connect(ui->pushButton_clearAll, SIGNAL(clicked()), this, SLOT(clearAllGrapf()));
//    connect(ui->pushButton_loadAll,SIGNAL(clicked()), plotAI1, SLOT(clearGrapf()));
 //   connect(ui->pushButton_clearAll,SIGNAL(clicked()), plotAI2, SLOT(clearGrapf()));
//    connect(ui->pushButton_clearAll,SIGNAL(clicked()), plotUI1, SLOT(clearGrapf()));
}



/**/
void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
    //statusBar()->showMessage(message);
}




/*
Парсинг полученной теапературы
маркер   UI1       AI1      AI2      SPI
"Temp   %02.02f  %02.02f  %02.02f %02.02f\r\n"
*/
void MainWindow::parseTemp(QByteArray data){
    showStatusMessage("parseTemp");
    qDebug()<<"MainWindow::parseTemp";
    qDebug()<<tr("%1").arg(data.data());
    QString str = QString(data);
    //QRegExp rx("(\\ |\\ |\\ |\\ |\\ )"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    //QStringList query = str.split(rx);
    //query.indexOf();
    qDebug() <<str.split(' ');
    QList<QString> lst = str.split(' ');

    //Если пришла нетемпература, просто выходим
    if(QString::compare(lst.at(0), "Temp", Qt::CaseInsensitive) != 0){
        printGraph(lst);
        return;
    }

    if(QString::compare(lst.at(0), "Status", Qt::CaseInsensitive) != 0){
        printGraph(lst);
        return;
    }

}

/**
Открываем временный файл для записи
*/
void MainWindow::openTmpFile(){
     //pathFile - это строка
    //file - это QFile
    //QString filter = tr("Temperature grapf (*.grapf):;;All file (*.*)");
    //   QString filter = tr("Temperature grapf (*.grapf)");
    pathFileTmp->clear();
    int n = 0;
    do{
        pathFileTmp->clear();
        pathFileTmp->append(tr("~tmpGrapf_%1.grapf").arg(n));
        n++;
    }while(fileTmp->exists(*pathFileTmp));

    fileTmp->setFileName(*pathFileTmp);
    if(fileTmp->isOpen())
        qDebug() << tr("ERROR: File already open");


    if(!fileTmp->open(QIODevice::ReadWrite)){
        qDebug() << tr("ERROR: File %1 not open").arg(file->fileName());
        return;
    }
}
/**
Пишем полученные данные во временный файл
*/
void MainWindow::writeTmpFile(QList<QString> lst){
    QByteArray str;
    str.clear();
    str.append(tr("Temp %1 %2 %3 %4\r\n")
            .arg(lst.at(WORK_TEMPERATURE))
            .arg(lst.at(AI1))
            .arg(lst.at(AI2))
            .arg(lst.at(UI1)));

    fileTmp->write(str);

}
/**
deviceStatus.workTemperatyre, //Уставка
deviceStatus.currentTemperature_AI1 //Текущая измеренная температура на датчике подключенном к AI1
deviceStatus.currentTemperature_AI2 //Текущая измеренная температура на датчике подключенном к AI2
deviceStatus.currentTemperature_UI1 //Текущая измеренная температура на датчике подключенном к UI1
deviceStatus.currentTemperature_SPI //Текущая измеренная температура на датчике подключенном к SPI
*/
void MainWindow::printGraph(QList<QString> lst){
    double workTemp = lst.at(WORK_TEMPERATURE).toDouble();
    double ai1 = lst.at(AI1).toDouble();
    double ai2 = lst.at(AI2).toDouble();
    double ui1 = lst.at(UI1).toDouble();

    plotAI1->printGraph(workTemp, ai1);
    plotAI2->printGraph(workTemp, ai2);
    plotUI1->printGraph(workTemp, ui1);
    writeTmpFile(lst);
}

/*
Парсим статус устройства и выводим на отображение
*/
void MainWindow::printStatus(QList<QString> lst){

}

/**/
void MainWindow::clearAllGrapf(){
    plotAI1->clearGrapf();
    plotAI2->clearGrapf();
    plotUI1->clearGrapf();
}

void MainWindow::on_pushButton_loadAll_clicked()
{
    //pathFile - это строка
    //file - это QFile
    QString filter = tr("Temperature grapf (*.grapf):;;All file (*.*)");
    //   QString filter = tr("Temperature grapf (*.grapf)");
    pathFile->clear();
    pathFile->append(QFileDialog::getOpenFileName(this, "Open a file", "", filter));

    file->setFileName(*pathFile);
    if(file->isOpen())
        qDebug() << tr("ERROR: File already open");


    if(!file->open(QIODevice::ReadWrite)){
        qDebug() << tr("ERROR: File %1 not open").arg(file->fileName());
        return;
    }


    quint64 numOfStr = 0;
    QTextStream in(file);
    QByteArray qbArray;
    while (!in.atEnd())
    {
       //QString line =
        //line = in.readLine();
       numOfStr++;
       qbArray.append(in.readLine());
       parseTemp(qbArray);
       qbArray.clear();
    }

    qDebug() << tr("Прочитано %1 строк").arg(numOfStr);
    file->close();


}

/**

*/
void MainWindow::writeToLog(QString *str){
    ui->log->appendPlainText(*str);

}
