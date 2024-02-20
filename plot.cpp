#include "plot.h"
#include "ui_plot.h"

/**/
Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
}

/**/
Plot::Plot(QString *plotName, double _xBegin, double _xEnd,  double _yBegin, double _yEnd,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    xPos = 0;
    ui->setupUi(this);
    ui->labelPlotName->setText(*plotName);
    xBegin = _xBegin;
    xEnd = _xEnd;
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(_yBegin, _yEnd);

}

/**/
Plot::~Plot()
{
    delete ui;
}

void Plot::printTestGraph(double ydata)
{
    if(xPos == ((int)xEnd-2)){
        xEnd = xEnd +1;
        ui->widget->xAxis->setRange(xBegin, xEnd);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(xPos,ydata);
    ui->widget->replot();
    xPos++;
}

