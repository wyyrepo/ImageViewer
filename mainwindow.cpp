#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileSystemModel>
#include <QImage>
#include <QIcon>
#include <QPainter>
#include <QtCore>
#include <QMessageBox>

#include <QImageReader>
#include <QFileIconProvider>
#include <QPushButton>

#include "widgetimage.h"
#include <QtConcurrent>


const int WIDTH_ICON = 100;
const int HEIGHT_ICON = 90;

const int WIDTH_IMAGE = 90;
const int HEIGHT_IMAGE = 65;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastClickedDir_("")
{
    ui->setupUi(this);

    ui->tabMain->removeTab(1);    


    QObject::connect(ui->treeWidgetFileSystem, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(treeWidget_itemExpanded(QTreeWidgetItem*)));
    QObject::connect(ui->treeWidgetFileSystem, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(treeWidget_itemClicked(QTreeWidgetItem*,int)));   
    QObject::connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(listWidget_itemDoubleClicked(QListWidgetItem*)));
    QObject::connect(ui->tabMain, SIGNAL(tabCloseRequested(int)), this, SLOT(tabMain_tabCloseRequested(int)));
    QObject::connect(ui->tabMain, SIGNAL(currentChanged(int)), this, SLOT(tabMain_currentChanged(int)));

    imagesShow_ = new QFutureWatcher<QImage>(this);
    connect(imagesShow_, SIGNAL(resultReadyAt(int)), SLOT(setItemInList(int)));
    connect(imagesShow_, SIGNAL(finished()), SLOT(finished()));

    AddItemToTreeWidgetFileSystem();

    QStatusBar *bar = new QStatusBar(this);
    this->setStatusBar(bar);
    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}





void  MainWindow::WaitFuture()
{
    if (imagesShow_->isRunning())
    {
        imagesShow_->cancel();
        imagesShow_->waitForFinished();
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    WaitFuture();
}


QPixmap prepareIcon(const QFileInfo &infoFile)
{
    QImage imageIcon(QLatin1String(":Images/Image.png"));
    imageIcon = imageIcon.scaledToHeight(HEIGHT_IMAGE, Qt::SmoothTransformation);

    int image_width = imageIcon.width();
    int image_height = imageIcon.height();

    QRectF target((WIDTH_ICON - image_width) / 2, 0, image_width, image_height);
    QRectF source(0, 0, image_width, image_height);


    QPixmap pixDraw(QSize(WIDTH_ICON, HEIGHT_ICON));
    QPainter painter(&pixDraw);

    painter.setBrush(Qt::NoBrush);
    painter.fillRect(QRect(0, 0, WIDTH_ICON, HEIGHT_ICON), Qt::white);


    painter.setPen(Qt::black);
    painter.drawImage(target, imageIcon, source);
    painter.drawRect(target);


    painter.setPen(Qt::darkBlue);

    QRect rect((WIDTH_ICON - image_width) / 2, image_height + 2, image_width, HEIGHT_ICON - image_height - 4);
    QFontMetrics font_metrics(painter.font());
    QString elideText = font_metrics.elidedText(infoFile.completeBaseName(), Qt::ElideRight, image_width);
    painter.drawText(rect, Qt::AlignCenter | Qt::ElideRight, elideText);

    return pixDraw;
}




QImage prepareImage(const QFileInfo &infoFile)
{
    QImageReader imageReader(infoFile.filePath());
    QSize size;
    int image_width = WIDTH_IMAGE;
    int image_height = HEIGHT_IMAGE;

    if (imageReader.supportsOption(QImageIOHandler::Size))
    {
        size = imageReader.size();
        image_width = size.width();
        image_height = size.height();
    }

    double ratio = (double)image_width / (double)image_height;
    image_height = HEIGHT_IMAGE;
    image_width = ratio * image_height;

    imageReader.setScaledSize(QSize(image_width, image_height));
    QImage image = imageReader.read();



    if (image.isNull())
    {
        QImage imageIcon(QLatin1String(":Images/Image.png"));
        image = imageIcon;
        image = image.scaledToHeight(HEIGHT_IMAGE, Qt::SmoothTransformation);

        image_width = image.width();
        image_height = image.height();
    }


    QRectF target((WIDTH_ICON - image_width) / 2, 0, image_width, image_height);
    QRectF source(0, 0, image_width, image_height);


    QImage imgDraw(QSize(WIDTH_ICON, HEIGHT_ICON), QImage::Format_RGB32);
    QPainter painter(&imgDraw);

    painter.setBrush(Qt::NoBrush);
    painter.fillRect(QRect(0, 0, WIDTH_ICON, HEIGHT_ICON), Qt::white);


    painter.setPen(Qt::black);
    painter.drawImage(target, image, source);
    painter.drawRect(target);

    painter.setPen(Qt::darkBlue);

    QRect rect((WIDTH_ICON - WIDTH_IMAGE) / 2, image_height + 2, WIDTH_IMAGE, HEIGHT_ICON - image_height - 4);
    QFontMetrics font_metrics(painter.font());
    QString elideText = font_metrics.elidedText(infoFile.completeBaseName(), Qt::ElideRight, WIDTH_IMAGE);
    painter.drawText(rect, Qt::AlignCenter | Qt::ElideRight, elideText);

    return (imgDraw);
}




void MainWindow::setItemInList(int index)
{    
    ui->listWidget->item(index)->setIcon(QIcon(QPixmap::fromImage(imagesShow_->resultAt(index))));

}

void MainWindow::finished()
{
}




void MainWindow::ShowImageIconFile(QString dirPath)
{   
    WaitFuture();   
    ui->listWidget->clear();
    fileList_ = getListFiles(dirPath);
    int count = fileList_.count();

    for (int i = 0; i < count; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(prepareIcon(fileList_[i])));
        item->setData(Qt::WhatsThisRole, QString(fileList_[i].filePath()));        
        ui->listWidget->addItem(item);
    }

    imagesShow_->setFuture(QtConcurrent::mapped(fileList_, prepareImage));
}





void MainWindow::AddItemToTreeWidgetFileSystem()
{
    QFileInfoList listDrives = QDir::drives();
    int count_drives = listDrives.count();

    QTreeWidgetItem *parentItem = ui->treeWidgetFileSystem->invisibleRootItem();

    for (int i = 0; i < count_drives; ++i)
    {
        if (listDrives[i].isReadable())
        {
            QTreeWidgetItem *item = new QTreeWidgetItem;
            QString strDrv = listDrives[i].filePath();
            strDrv.remove(strDrv.length() - 1, 1);
            item->setText(0, strDrv);
            item->setIcon(0, QFileIconProvider().icon(listDrives[i]));
            item->setData(0, Qt::WhatsThisRole, listDrives[i].absoluteFilePath());

            QTreeWidgetItem *subitem = new QTreeWidgetItem;
            subitem->setData(0, Qt::WhatsThisRole, QString("@@@"));
            subitem->setText(0, listDrives[i].filePath());
            item->addChild(subitem);
            parentItem->addChild(item);
        }
    }
}



 void MainWindow::treeWidget_itemExpanded(QTreeWidgetItem *item)
 {
     int child_count = item->childCount();
     QString data = item->child(0)->data(0, Qt::WhatsThisRole).toString();

     if (child_count == 1 && data == QString("@@@"))
     {
         QString strPath = item->child(0)->text(0);
         QDir dir(strPath);

         item->takeChild(0);

         QFileInfoList dirList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
         int count_dirs = dirList.count();

         for (int i = 0; i < count_dirs; ++i)
         {
             QTreeWidgetItem *subitem = new QTreeWidgetItem;
             QString strDrv = dirList[i].fileName();
             subitem->setText(0, strDrv);
             subitem->setIcon(0, QFileIconProvider().icon(dirList[i]));
             subitem->setData(0, Qt::WhatsThisRole, dirList[i].absoluteFilePath());

             QDir dirSub(dirList[i].filePath());
             QFileInfoList dirSubList = dirSub.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

             if (dirSubList.count() > 0)
             {
                QTreeWidgetItem *subsubitem = new QTreeWidgetItem;
                subsubitem->setData(0, Qt::WhatsThisRole, QString("@@@"));
                subsubitem->setText(0, dirList[i].filePath());
                subitem->addChild(subsubitem);
             }

             item->addChild(subitem);
         }
     }
 }


 void MainWindow::treeWidget_itemClicked(QTreeWidgetItem *item, int column)
 {
     QString strDirPath = item->data(0, Qt::WhatsThisRole).toString();

     if (strDirPath != lastClickedDir_)
     {
        ShowImageIconFile(strDirPath);
     }

     lastClickedDir_ = strDirPath;

     this->setWindowTitle(lastClickedDir_);
 }



 void MainWindow::tabMain_tabCloseRequested(int index_tab)
 {
     if (index_tab == 0)
         this->close();

     ui->tabMain->removeTab(index_tab);
 }


void MainWindow::tabMain_currentChanged(int index_tab)
{
    if (index_tab == 0)
    {
        statusBar()->showMessage(tr("Ready"));
    }
    else
    {
        ((WidgetImage *)(ui->tabMain->widget(index_tab)))->UpdateStatusBar();
    }
}


 QFileInfoList MainWindow::getListFiles(QString dirPath) const
 {
     QDir dir(dirPath);

     QStringList filters;
     filters << "*.jpg" << "*.jpeg" << "*.png" << ".bmp" << "tiff" << "ico";
     dir.setNameFilters(filters);

     return dir.entryInfoList(filters, QDir::Files);
 }



 void MainWindow::listWidget_itemDoubleClicked(QListWidgetItem *item)
 {
     QString strDirPath = item->data(Qt::WhatsThisRole).toString();

     WidgetImage *widget = new WidgetImage();
     widget->setGeometry(0, 0, ui->tabMain->width(), ui->tabMain->height());
     widget->SetImage(strDirPath, fileList_, this->statusBar(), ui->tabMain, ui->tabMain->count());

     ui->tabMain->addTab(widget, strDirPath);
     ui->tabMain->setCurrentWidget(widget);
 }
