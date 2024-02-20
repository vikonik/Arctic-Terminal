#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qcustomplot.h"
#include "plot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

