/********************************************************************************
** Form generated from reading UI file 'hades.ui'
**
** Created: Tue Sep 25 13:26:51 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HADES_H
#define UI_HADES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HadesClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *HadesClass)
    {
        if (HadesClass->objectName().isEmpty())
            HadesClass->setObjectName(QString::fromUtf8("HadesClass"));
        HadesClass->resize(558, 447);
        centralWidget = new QWidget(HadesClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        HadesClass->setCentralWidget(centralWidget);

        retranslateUi(HadesClass);

        QMetaObject::connectSlotsByName(HadesClass);
    } // setupUi

    void retranslateUi(QMainWindow *HadesClass)
    {
        HadesClass->setWindowTitle(QApplication::translate("HadesClass", "Hades", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HadesClass: public Ui_HadesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HADES_H
