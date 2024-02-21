/*
#include "BinModel01.h"
#include "Option02.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double S0,U,D,R;
    if (GetInputData(S0,U,D,R)==1) return 1;
    
        double K; //strike price
        double N; //steps to exipiry

        cout << "Enter call optio data: " << endl;
        GetInputData(&N,&K);
        cout << "European call option price = "
             << PriceByCRR(S0,U,D,R,N,K)
             << endl << endl;
    
    return 0;
}  
*/