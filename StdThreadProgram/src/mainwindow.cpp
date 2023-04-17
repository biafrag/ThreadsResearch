#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calculo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _calculo = new Calculo();
    _thread = std::thread(&Calculo::doCalculus, _calculo);

    connect(_calculo, &Calculo::finished,
         [](float result)
         {
            printf("Result: %f\n", result);
         });
}

MainWindow::~MainWindow()
{
    delete ui;
    _thread.join();

}

