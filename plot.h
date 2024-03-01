#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>

namespace Ui {
class Plot;
}

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    explicit Plot(QString *plotName, double _xBegin, double _xEnd, double _yBegin, double _yEnd, QWidget *parent = nullptr);
    ~Plot();

    void printTestGraph(double ydata);
    void plotTestInit();
    void showContextMenu(const QPoint &pos);
    void initButtons();

public slots:
    void printGraph(double workTemp, double data);

    void mouseTest(QMouseEvent *event);
    void clearGrapf();

    void testSignal();
    void mousePressEvent(QMouseEvent *event);
    void slotCustomMenuRequested();

private slots:
    void on_pushButton_clear_clicked();

private:
    Ui::Plot *ui;

    double xBegin, xEnd,h, X;
    double xEndDefault = 50;//Размер при сбросе
    int xPos;

    QMenu *menu;
   //QWidget *widget;
    QAction *propGrahp;
    QAction *item1;
    QAction *item2;
    QAction *item3;
};

#endif // PLOT_H
