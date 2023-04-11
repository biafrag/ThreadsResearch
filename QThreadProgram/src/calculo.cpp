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
//    if(this->thread() == QApplication::instance()->thread())
//    {
//        printf("Eh a main thread\n");
//    }
//    else
//    {
//        printf("Nao eh a main thread\n");
//    }

    float count = 0;

    for(int j = 0; j < INT_MAX; j++)
    {
        count += sqrt(23 * j);
    }

    emit finished(count);
}

