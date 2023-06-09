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
    connect(calculoThread, &QThread::finished, _calculo, &Calculo::deleteLater);
    connect(ui->pushButton, &QPushButton::clicked, _calculo, &Calculo::doCalculus);

    connect(_calculo, &Calculo::finished,
         [](float result)
         {
            printf("Result: %f\n", result);
         });
     calculoThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

