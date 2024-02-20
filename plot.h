#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

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
private:
    Ui::Plot *ui;

    double xBegin, xEnd,h, X;
    int xPos;
};

#endif // PLOT_H
