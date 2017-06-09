/********************************************************************************
** Form generated from reading UI file 'signature.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNATURE_H
#define UI_SIGNATURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Signature
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_identity;
    QComboBox *comboBox_sign_file;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_provision;
    QLineEdit *lineEdit_provision;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_file;
    QPushButton *pushButton_start;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView_main;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Signature)
    {
        if (Signature->objectName().isEmpty())
            Signature->setObjectName(QStringLiteral("Signature"));
        Signature->resize(1000, 680);
        centralWidget = new QWidget(Signature);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_identity = new QLabel(centralWidget);
        label_identity->setObjectName(QStringLiteral("label_identity"));

        horizontalLayout->addWidget(label_identity);

        comboBox_sign_file = new QComboBox(centralWidget);
        comboBox_sign_file->setObjectName(QStringLiteral("comboBox_sign_file"));
        comboBox_sign_file->setMinimumSize(QSize(300, 40));
        comboBox_sign_file->setMaximumSize(QSize(300, 40));

        horizontalLayout->addWidget(comboBox_sign_file);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_provision = new QPushButton(centralWidget);
        pushButton_provision->setObjectName(QStringLiteral("pushButton_provision"));
        pushButton_provision->setMinimumSize(QSize(100, 40));
        pushButton_provision->setMaximumSize(QSize(100, 40));

        horizontalLayout->addWidget(pushButton_provision);

        lineEdit_provision = new QLineEdit(centralWidget);
        lineEdit_provision->setObjectName(QStringLiteral("lineEdit_provision"));
        lineEdit_provision->setMinimumSize(QSize(300, 30));
        lineEdit_provision->setMaximumSize(QSize(300, 30));

        horizontalLayout->addWidget(lineEdit_provision);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_file = new QPushButton(centralWidget);
        pushButton_file->setObjectName(QStringLiteral("pushButton_file"));
        pushButton_file->setMinimumSize(QSize(100, 40));
        pushButton_file->setMaximumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(pushButton_file);

        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setMinimumSize(QSize(100, 40));
        pushButton_start->setMaximumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(pushButton_start);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tableView_main = new QTableView(centralWidget);
        tableView_main->setObjectName(QStringLiteral("tableView_main"));

        gridLayout->addWidget(tableView_main, 2, 0, 1, 1);

        Signature->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Signature);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        Signature->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Signature);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Signature->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(Signature);

        QMetaObject::connectSlotsByName(Signature);
    } // setupUi

    void retranslateUi(QMainWindow *Signature)
    {
        Signature->setWindowTitle(QApplication::translate("Signature", "Signature", 0));
        label_identity->setText(QApplication::translate("Signature", "\347\255\276\345\220\215\346\226\207\344\273\266\357\274\232", 0));
        pushButton_provision->setText(QApplication::translate("Signature", "provision", 0));
        pushButton_file->setText(QApplication::translate("Signature", "\351\200\211\346\213\251ipa\346\226\207\344\273\266", 0));
        pushButton_start->setText(QApplication::translate("Signature", "\345\274\200\345\247\213\347\255\276\345\220\215", 0));
    } // retranslateUi

};

namespace Ui {
    class Signature: public Ui_Signature {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNATURE_H
