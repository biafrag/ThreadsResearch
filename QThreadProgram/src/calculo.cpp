#include "include/calculo.h"
#include <limits.h>
#include "math.h"
#include "stdio.h"
Calculo::Calculo()
{
}



Calculo::~Calculo()
{
}



float Calculo::doCalculus()
{
    float count = 0;
    for(int i = 0; i < INT_MAX; i++)
    {
        for(int j = 0; j < INT_MAX; j++)
        {
            count += sqrt(23 * i);
        }
    }
   // printf("%f\n", count);
    return count;
}

