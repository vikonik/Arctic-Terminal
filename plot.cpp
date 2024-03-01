#include "plot.h"
#include "ui_plot.h"
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

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



connect(ui->widget,SIGNAL(mousePress(QMouseEvent*)),this, SLOT(mousePressEvent(QMouseEvent*)));
 qDebug() << "Construtor of ContextMenu class";
initButtons();

//Контекстное меню
menu = new QMenu(this);
QAction *menuClearGrapf = new QAction(tr("Очистить"));
menu->addAction(menuClearGrapf);
connect(menuClearGrapf, &QAction::triggered, this, &Plot::clearGrapf);
}

void Plot::mousePressEvent (QMouseEvent *event){
    switch (event->button()) {
        case Qt::LeftButton:
        {
            qDebug() << "Left Mouse button pressed";
            break;
        }
        case Qt::RightButton:
        {
            qDebug() << "Left Mouse button pressed";
            slotCustomMenuRequested();
            break;
        }
        case Qt::MiddleButton:
        {
            qDebug() << "Middle Mouse button pressed";
            break;
        }
        default:
        {
            qDebug() << "Other button pressed, id = "+QString::number(event->button());
            break;
        }
    }
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
    ui->widget->graph(0)->data().data()->clear();
    ui->widget->graph(1)->data().data()->clear();
    this->xPos = 0;//Устанавливаем в начало
    ui->widget->xAxis->setRange(xBegin, xEndDefault);//Восстанавливаем размер графика
    ui->widget->replot();

}

/**/
void Plot::initButtons(){
//    ui->pushButton_loadData->setEnabled(false);
//    ui->pushButton_saveData->setEnabled(false);

}

/**
Запускаем контекстное меню
*/
void Plot::slotCustomMenuRequested()
{
    menu->exec(QCursor::pos());
}
