/********************************************************************************
** Form generated from reading UI file 'plot.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plot
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelPlotName;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *widget;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_loadData;
    QPushButton *pushButton_saveData;

    void setupUi(QWidget *Plot)
    {
        if (Plot->objectName().isEmpty())
            Plot->setObjectName(QString::fromUtf8("Plot"));
        Plot->resize(1037, 232);
        verticalLayout = new QVBoxLayout(Plot);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelPlotName = new QLabel(Plot);
        labelPlotName->setObjectName(QString::fromUtf8("labelPlotName"));
        labelPlotName->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelPlotName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget = new QCustomPlot(Plot);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout_2->addWidget(widget);

        widget_3 = new QWidget(Plot);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton_clear = new QPushButton(widget_3);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        verticalLayout_2->addWidget(pushButton_clear);

        pushButton_loadData = new QPushButton(widget_3);
        pushButton_loadData->setObjectName(QString::fromUtf8("pushButton_loadData"));

        verticalLayout_2->addWidget(pushButton_loadData);

        pushButton_saveData = new QPushButton(widget_3);
        pushButton_saveData->setObjectName(QString::fromUtf8("pushButton_saveData"));

        verticalLayout_2->addWidget(pushButton_saveData);


        horizontalLayout_2->addWidget(widget_3);

        horizontalLayout_2->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(1, 1);

        retranslateUi(Plot);

        QMetaObject::connectSlotsByName(Plot);
    } // setupUi

    void retranslateUi(QWidget *Plot)
    {
        Plot->setWindowTitle(QCoreApplication::translate("Plot", "Form", nullptr));
        labelPlotName->setText(QCoreApplication::translate("Plot", "TextLabel", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Plot", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        pushButton_loadData->setText(QCoreApplication::translate("Plot", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        pushButton_saveData->setText(QCoreApplication::translate("Plot", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Plot: public Ui_Plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
