#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "qcustomplot.h"
#include <QVector>
#include "plot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
Plot *plotAI1;
Plot *plotAI2;
Plot *plotUI1;


    QVector<double> x,y;
};
#endif // MAINWINDOW_H
