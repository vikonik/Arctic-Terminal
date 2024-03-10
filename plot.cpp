#include "plot.h"
#include "ui_plot.h"
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QDir>
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
    maxY = 0.0;
    minY = 80.0;

    ui->setupUi(this);
    ui->labelPlotName->setText(*plotName);
    xBegin = _xBegin;
    xEnd = _xEnd;
    yBegin = _yBegin;
    yEnd = _yEnd;
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(_yBegin, _yEnd);



connect(ui->widget,SIGNAL(mousePress(QMouseEvent*)),this, SLOT(mousePressEvent(QMouseEvent*)));
 qDebug() << "Construtor of ContextMenu class";
initButtons();

//Контекстное меню
menu = new QMenu(this);
QAction *menuClearGrapf = new QAction(tr("Очистить"));
QAction *menuSeveGrapfToJpg = new QAction(tr("Сохранить как картинку"));
QAction *menuZoomPlus = new QAction(tr("Увеличить"));
QAction *menuZoomMinus = new QAction(tr("Уменьшить"));

menu->addAction(menuClearGrapf);
menu->addAction(menuSeveGrapfToJpg);
menu->addAction(menuZoomPlus);
menu->addAction(menuZoomMinus);
//menuSeveGrapfToJpg->setEnabled(false);
connect(menuClearGrapf, &QAction::triggered, this, &Plot::clearGrapf);
connect(menuSeveGrapfToJpg, &QAction::triggered, this, &Plot::saveToJpg);
connect(menuZoomPlus, &QAction::triggered, this, &Plot::zoomPlus);
connect(menuZoomMinus, &QAction::triggered, this, &Plot::zoomMinus);
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
        xEnd = xEnd +5;
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
    qDebug() << tr("xPos %1, xEnd %2").arg(xPos).arg(xEnd);
    if(xPos >= ((int)xEnd-2)){
        xEnd = xEnd +1;
        ui->widget->xAxis->setRange(xBegin, xEnd);
        ui->widget->replot();
    }

    /*
    minY = std::min({workTemp, data, minY - 3});
    maxY = std::max({workTemp, data, maxY + 1});
    ui->widget->yAxis->setRange(minY, maxY);
*/
    if(data < workTemp && data < minY){
        minY = data;

        ui->widget->yAxis->setRange(minY -3, maxY+1);
    }
    if(workTemp < data && workTemp < minY){
        minY = workTemp;
        ui->widget->yAxis->setRange(minY -3, maxY+1);
    }

    if(data > workTemp && data > maxY){
        maxY = data;
        ui->widget->yAxis->setRange(minY -3, maxY+1);
    }
    if(workTemp > data && workTemp > maxY){
        maxY = workTemp;
        ui->widget->yAxis->setRange(minY -3, maxY+1);
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
    this->xEnd = 10;
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

/**
Сохраняем картинку как jpg
*/
void Plot::saveToJpg(){
     qDebug() << "saveToJpg";

     QString pathFileToSave ="";
     QString filter = tr("Temperature jpg (*.jpg):;;All file (*.*)");
     pathFileToSave.clear();
     pathFileToSave.append(QFileDialog::getSaveFileName(this, "Save a file", "", filter));
     QFile file(pathFileToSave);

     if (!file.open(QIODevice::WriteOnly))
     {
         qDebug() << file.errorString();
     } else {
         ui->widget->saveJpg(pathFileToSave);
     }

}

/**/
void Plot::zoomPlus(){
    ui->widget->yAxis->setRange(yBegin, yEnd -=yEnd/2);
    ui->widget->replot();
}

void Plot::zoomMinus(){
    ui->widget->yAxis->setRange(yBegin, yEnd +=yEnd/2);
    ui->widget->replot();
}
