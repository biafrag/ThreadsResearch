#include "include/calculo.h"
#include <limits.h>
#include "math.h"
#include "stdio.h"
#include <QApplication>
Calculo::Calculo()
{
}



Calculo::~Calculo()
{
}



void Calculo::doCalculus()
{

    float count = 0;

    for(int j = 0; j < INT_MAX; j++)
    {
        count *= sqrt(j);
    }

    emit finished(count);
}

