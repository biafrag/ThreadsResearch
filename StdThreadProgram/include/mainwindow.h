#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Calculo;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::thread _thread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Calculo *_calculo;
    int _count = 0;

};
#endif // MAINWINDOW_H
