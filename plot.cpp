#include "plot.h"
#include "ui_plot.h"
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>

/**/
Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);
    //initButtons();
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
connect(ui->pushButton_clear,SIGNAL(clicked()), this, SLOT(clearGrapf()));
connect(ui->widget,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mouseTest(QMouseEvent*)));
//connect(ui->widget,SIGNAL(mousePressEvent(QMouseEvent*)),this,SLOT(mouseTest(QMouseEvent*)));
 qDebug() << "Construtor of ContextMenu class";
initButtons();
}

/**/
void Plot::mouseTest(QMouseEvent* event){
    qDebug() << "mouseTest";
    QPoint point = event->pos();
qDebug() << ui->widget->xAxis->pixelToCoord(point.x()) << ui->widget->yAxis->pixelToCoord(point.y());

}

void Plot::testSignal(){
     qDebug() << "testSignal";

}
/**/
Plot::~Plot()
{
    delete ui;
}

/*
Потренируемся...
*/
void Plot::plotTestInit(){
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen (Qt :: red));
    ui->widget->graph(1)->setPen(QPen (Qt :: blue));
}
void Plot::printTestGraph(double ydata)
{
    if(xPos == ((int)xEnd-2)){
        xEnd = xEnd +1;
        ui->widget->xAxis->setRange(xBegin, xEnd);
    }
//    ui->widget->addGraph();
    ui->widget->graph(0)->addData(xPos,ydata);
    ui->widget->graph(1)->addData(xPos,ydata/2);
    ui->widget->replot();
    xPos++;

}

/*
Вывод данных на график
*/
void Plot::printGraph(double workTemp, double data)
{
    if(xPos == ((int)xEnd-2)){
        xEnd = xEnd +1;
        ui->widget->xAxis->setRange(xBegin, xEnd);
    }
    ui->widget->graph(0)->addData(xPos,data);
    ui->widget->graph(1)->addData(xPos,workTemp);
    ui->widget->replot();
    xPos++;
}


/*
Очищаем график
*/
void Plot::on_pushButton_clear_clicked()
{

}
/**/
void Plot::clearGrapf(){
    qDebug() << "clearGrapf";
    //ui->widget->clearGraphs();
    //ui->widget->clearItems();
    //ui->widget->clearPlottables();
    ui->widget->graph(0)->data().data()->clear();
    ui->widget->graph(1)->data().data()->clear();
    this->xPos = 0;//Устанавливаем в начало
    ui->widget->xAxis->setRange(xBegin, xEndDefault);//Восстанавливаем размер графика
    ui->widget->replot();

}

/**/
void Plot::initButtons(){
    ui->pushButton_loadData->setEnabled(false);
    ui->pushButton_saveData->setEnabled(false);

}
