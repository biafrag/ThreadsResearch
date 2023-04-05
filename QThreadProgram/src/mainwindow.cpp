#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calculo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    calculoThread.quit();
    calculoThread.wait();
}


void MainWindow::on_pushButton_clicked()
{
    Calculo *c = new Calculo();
    c->moveToThread(&calculoThread);
    connect(&calculoThread, &QThread::finished, c, &QObject::deleteLater);
    calculoThread.start();
    c->doCalculus();

}

