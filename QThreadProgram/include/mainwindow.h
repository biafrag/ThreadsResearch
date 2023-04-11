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
    QThread *calculoThread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Calculo *_calculo;
    int _count = 0;
};
#endif // MAINWINDOW_H
