#include "Options02.h"
#include "BinModel01.h"
#include <iostream>
#include <cmath>
using namespace std;


/*
A pointer is a variable used to store an address in computer memory.
For example, a pointer called Ptr in which to store the address of a variable of type double is declared by
double* Ptr;
Then *Ptr can be used to access the value of that variable
Then *Ptr can be used to access the value of that variable. For example, *Ptr=1.6
means that value 1.6 of type double will be stored at the address held (we often say, pointed to) by Ptr. We can use *Ptr whenever we would normally use a variable of type double.
On the other hand, if x is a variable of type double declared by double x;
then &x designates the address of x, and we can set
Ptr=&x;
if we want Ptr to point to x (that is, to hold the address of x).
*/

int GetInputData(int* PtrN,double* PtrK)
{
    cout << "Enter steps to expiry N ";cin >> *PtrN;
    cout <<"Enter strike price K: "   ;cin >> *PtrK;
    cout << endl;
    return 0;
}

double PriceByCRR(double S0,double U,double D,
                double R, int N, double K)

{
    double q=RiskNeutProb(U,D,R);
    double Price[N+1];
    for (int i = 0; i <= N; i++)
    {
        *(Price+i)=CallPayoff(S(S0,U,D,N,i),K);
    }
    for (int n = N-1; n >= 0; n--)
    {
        for (int i = 0; i <= n; i++)
        {
            *(Price+i) = (q*(*(Price+i+1))+(1-q)*(*(Price+i)))/(1+R);
        }
    }
    return *Price;
}
double CallPayoff(double z,double K)
{
    if (z>K)
    {
        return z-K;
    }
    return 0.0;
}