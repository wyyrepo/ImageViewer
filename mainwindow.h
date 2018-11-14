#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QListWidget>
#include <QFuture>
#include <QTreeWidgetItem>

#include "addiconimagethread.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void treeWidget_itemExpanded(QTreeWidgetItem *item);
    void treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void listWidget_itemDoubleClicked(QListWidgetItem *item);
    void tabMain_tabCloseRequested(int index_tab);
    void tabMain_currentChanged(int index_tab);

private Q_SLOTS:    
    void setItemInList(int index);
    void finished();   

private:
    Ui::MainWindow *ui;    
    QFutureWatcher<QImage> *imagesShow_;

    void ShowImageIconFile(QString dirPath);
    void WaitFuture();
    void AddItemToTreeWidgetFileSystem();
    QFileInfoList getListFiles(QString dirPath) const;

private:
    QString lastClickedDir_;
    QFileInfoList fileList_;
};

QPixmap prepareIcon(const QFileInfo &infoFile);
//QPixmap prepareImage(const QFileInfo &infoFile);
QImage prepareImage(const QFileInfo &infoFile);

#endif // MAINWINDOW_H
