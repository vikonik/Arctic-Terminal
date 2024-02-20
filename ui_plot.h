/********************************************************************************
** Form generated from reading UI file 'plot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plot
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelPlotName;
    QCustomPlot *widget;

    void setupUi(QWidget *Plot)
    {
        if (Plot->objectName().isEmpty())
            Plot->setObjectName(QString::fromUtf8("Plot"));
        Plot->resize(400, 300);
        verticalLayout = new QVBoxLayout(Plot);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelPlotName = new QLabel(Plot);
        labelPlotName->setObjectName(QString::fromUtf8("labelPlotName"));
        labelPlotName->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelPlotName);

        widget = new QCustomPlot(Plot);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(1, 1);

        retranslateUi(Plot);

        QMetaObject::connectSlotsByName(Plot);
    } // setupUi

    void retranslateUi(QWidget *Plot)
    {
        Plot->setWindowTitle(QApplication::translate("Plot", "Form", nullptr));
        labelPlotName->setText(QApplication::translate("Plot", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Plot: public Ui_Plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
