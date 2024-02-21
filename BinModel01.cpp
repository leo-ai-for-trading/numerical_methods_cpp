/*
In the binomial model the prices of assets evolve in discrete time steps $n=0,1,2, \ldots$. There is a stock whose price evolves randomly by moving up by a factor $1+U$ or down by $1+D$ independently at each time step, starting from the spot price $S(0)$. As a result, the stock price becomes
$$
S(n, i)=S(0)(1+U)^i(1+D)^{n-i}
$$
at step $n$ and node $i$ in the binomial tree
Within the binomial model the price $H(n, i)$ 
at each time step $n$ and node $i$ of a European option 
with expiry date $N$ and payoff $h(S(N))$ can be computed using the Cox-Ross-Rubinstein (CRR) procedure, which proceeds by backward induction:
*/
#include <iostream>
#include <cmath>
using namespace std;


//compute risk-neutral probability
double RiskNeutProb(double U, double D, double R)
{
    return (R-D)/(U-D);
}
//compute stock price at node n=3,i=2
double S(double S0,double U, double D, int n, int i)
{
    return S0*pow(1+U,i)*pow(1+D,n-i);
}

//input, display and checking model data
/*When defining a function to handle input data we 
face a problem be- cause a function 
in C++ can return only a single value, 
but we want to enter four numbers as inputs, 
and the function will need to pass all of them to the program. 
To deal with this, in the arguments are passed by reference, 
which is indicated by &
*/
int GetInputData(double& S0,
                double& U,double& D,double& R)
{
    //entering data
    cout << "Enter S0: "; cin >> S0;
    cout << "Enter U: "; cin >> U;
    cout << "Enter D: "; cin >> D;
    cout << "Enter R: "; cin >> R;
    cout <<endl;
    //making sure that 0<S0, -1<D<U, -1<R
    if (S0<=0.0 || U<= -1.0 || D<=-1.0 || U<=D
        || R<=-1.0)
    {
        cout << "Illegal data ranges" << endl;
        cout << "Terminate program" << endl;
        return 1;
    }
    
    //checking for arbitrage
    if (R>=U || R<=D)
    {
        cout << "Arbitrage exists" << endl;
        cout << "Terminating program" << endl;
        return 1;
    }
    cout << "Input data checked" << endl;
    cout << "There is no arbitrage" << endl << endl;    
    return 0;
    
}

    int main()
{
    double S0, U, D, R;
    if (GetInputData(S0,U, D,R)==1 ) return 1;
    //compute risk-neutral probability
    cout <<"q= " << RiskNeutProb(U, D, R) << endl;
    
    //compute stock price at node n=3, i=2
    int n; int i=2;
    cout <<"n= " <<n<< endl;
    cout <<"i = " <<i<< endl;
    cout << "S(n,i) = "<<S(S0,U, D, n, i) << endl;
    return 0;
}