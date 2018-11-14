/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 22. Apr 15:58:35 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QListWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QToolBar>
#include <QTreeWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabMain;
    QWidget *tabFileSystem;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidgetFileSystem;
    QListWidget *listWidget;
    QWidget *tabImage;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(701, 380);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tabMain = new QTabWidget(centralWidget);
        tabMain->setObjectName(QString::fromUtf8("tabMain"));
        tabMain->setTabShape(QTabWidget::Rounded);
        tabMain->setTabsClosable(true);
        tabMain->setMovable(false);
        tabFileSystem = new QWidget();
        tabFileSystem->setObjectName(QString::fromUtf8("tabFileSystem"));
        horizontalLayout_3 = new QHBoxLayout(tabFileSystem);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeWidgetFileSystem = new QTreeWidget(tabFileSystem);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetFileSystem->setHeaderItem(__qtreewidgetitem);
        treeWidgetFileSystem->setObjectName(QString::fromUtf8("treeWidgetFileSystem"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidgetFileSystem->sizePolicy().hasHeightForWidth());
        treeWidgetFileSystem->setSizePolicy(sizePolicy);
        treeWidgetFileSystem->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        treeWidgetFileSystem->header()->setVisible(false);

        horizontalLayout->addWidget(treeWidgetFileSystem);

        listWidget = new QListWidget(tabFileSystem);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setAutoFillBackground(false);
        listWidget->setFrameShape(QFrame::StyledPanel);
        listWidget->setFrameShadow(QFrame::Sunken);
        listWidget->setIconSize(QSize(100, 100));
        listWidget->setTextElideMode(Qt::ElideRight);
        listWidget->setMovement(QListView::Static);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setResizeMode(QListView::Adjust);
        listWidget->setLayoutMode(QListView::SinglePass);
        listWidget->setSpacing(2);
        listWidget->setViewMode(QListView::IconMode);
        listWidget->setUniformItemSizes(false);
        listWidget->setBatchSize(80);
        listWidget->setWordWrap(true);

        horizontalLayout->addWidget(listWidget);


        horizontalLayout_3->addLayout(horizontalLayout);

        tabMain->addTab(tabFileSystem, QString());
        tabImage = new QWidget();
        tabImage->setObjectName(QString::fromUtf8("tabImage"));
        tabImage->setAutoFillBackground(false);
        tabMain->addTab(tabImage, QString());

        horizontalLayout_2->addWidget(tabMain);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 701, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "View images", 0));
        tabMain->setTabText(tabMain->indexOf(tabFileSystem), QApplication::translate("MainWindow", "Folders", 0));
        tabMain->setTabText(tabMain->indexOf(tabImage), QApplication::translate("MainWindow", "Image", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
