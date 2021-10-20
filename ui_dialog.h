/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QLabel *label_cin;
    QLabel *label_prenom;
    QLabel *label_nom;
    QLineEdit *lineEdit_cinD;
    QLineEdit *lineEdit_prenomD;
    QLineEdit *lineEdit_nomD;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 321, 231));
        label_cin = new QLabel(groupBox);
        label_cin->setObjectName(QStringLiteral("label_cin"));
        label_cin->setGeometry(QRect(30, 40, 56, 16));
        label_prenom = new QLabel(groupBox);
        label_prenom->setObjectName(QStringLiteral("label_prenom"));
        label_prenom->setGeometry(QRect(30, 100, 56, 16));
        label_nom = new QLabel(groupBox);
        label_nom->setObjectName(QStringLiteral("label_nom"));
        label_nom->setGeometry(QRect(30, 150, 56, 16));
        lineEdit_cinD = new QLineEdit(groupBox);
        lineEdit_cinD->setObjectName(QStringLiteral("lineEdit_cinD"));
        lineEdit_cinD->setGeometry(QRect(120, 40, 113, 22));
        lineEdit_cinD->setReadOnly(true);
        lineEdit_prenomD = new QLineEdit(groupBox);
        lineEdit_prenomD->setObjectName(QStringLiteral("lineEdit_prenomD"));
        lineEdit_prenomD->setGeometry(QRect(120, 100, 113, 22));
        lineEdit_prenomD->setReadOnly(true);
        lineEdit_nomD = new QLineEdit(groupBox);
        lineEdit_nomD->setObjectName(QStringLiteral("lineEdit_nomD"));
        lineEdit_nomD->setGeometry(QRect(120, 150, 113, 22));
        lineEdit_nomD->setReadOnly(true);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Afficher clients", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "Afficher client", Q_NULLPTR));
        label_cin->setText(QApplication::translate("Dialog", "cin", Q_NULLPTR));
        label_prenom->setText(QApplication::translate("Dialog", "prenom", Q_NULLPTR));
        label_nom->setText(QApplication::translate("Dialog", "nom", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
