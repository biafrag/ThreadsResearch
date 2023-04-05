#pragma once
#include <QObject>

class Calculo : public QObject
{
    Q_OBJECT

public:
    Calculo();
    ~Calculo();
    float doCalculus();

};
