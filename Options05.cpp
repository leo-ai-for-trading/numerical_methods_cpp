#include "Options05.h"
#include "BinModel02.h"
#include <iostream>
#include <cmath>
using namespace std;
/*
In GetInputData() we have to work a little bit harder 
to set the value of N compared with K. 
This is because N is a variable inherited from the 
EurOption class, declared as private in that class. 
As a result, the subclasses do not have direct access to 
it and have to use the SetN() function belonging to the 
EurOption class. Meanwhile, K is a vari- able defined within 
the subclasses Call and Put, which therefore have direct 
access to it.
*/

double EurOption::PriceByCRR(BinModel Model, double K)
{
    double q=Model.RiskNeutProb();
    double Price[N+1];
    for (int i = 0; i <= N; i++)
    {
        Price[i]=Payoff(Model.S(N,i),K);
    }
    for (int n = N-1; n >=0; n--)
    {
        for (int i = 0; i <= n; i++)
        {
            Price[i] = (q*Price[i+1]+(1-q)*Price[i])
                        /(1+Model.GetR());
        }
        
    }
    return Price[0];
}

double CallPayoff(double z,double K)
{
    if (z>K) return z-K;
    {
        return 0.0;
    }
}
int Call::GetInputData()
{
    cout << "Enter call option data:" << endl;
    int N;
    cout << "Enter steps to expiry N: "; cin >> N;
    SetN(N);
    cout << "Enter strike price K: "; cin >> K;
    cout << endl;
    return 0;
}
double PutPayoff(double z,double K)
{
    if (z<K) return K-z;
    {
        return 0.0;
    }
}
int Put::GetInputData()
{
   cout << "Enter put option data:" << endl;
   int N;
   cout << "Enter steps to expiry N: "; cin >> N;
   SetN(N);
   cout << "Enter strike price K:";     cin >> K;
   cout << endl;
   return 0;
}


