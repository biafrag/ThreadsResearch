#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calculo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calculoThread = new QThread();
    _calculo = new Calculo();
    _calculo->moveToThread(calculoThread);
    connect(calculoThread, &QThread::started, _calculo, &Calculo::doCalculus);
    connect( _calculo, &Calculo::finished, calculoThread, &QThread::quit);

    connect(calculoThread, &QThread::finished, calculoThread, &QThread::deleteLater);
    connect(_calculo, &Calculo::finished, _calculo, &Calculo::deleteLater);

    connect(_calculo, &Calculo::finished,
         [](float result)
         {

         });
     calculoThread->start();
     ui->countageLabel->setText(QString::number(_count));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    _calculo->doCalculus();
}


void MainWindow::on_pushButton_2_clicked()
{
    _count++;
    ui->countageLabel->setText(QString::number(_count));
}

