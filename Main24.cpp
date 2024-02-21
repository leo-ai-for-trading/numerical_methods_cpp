#include <iostream>
#include "BSModel01.h"
#include "Option.h"
#include "BSEq.h"
#include "ExplicitMethod.h"
/*
(3) We initialise an object BSPDE of class BSEq. It contains functions which
6.2 Explicit method
139
give the coefficients (6.6) of the Black-Scholes equation (6.5), together with the boundary conditions derived from EuropeanPut (see Listing 6.5).
4 Method is the explicit method, with the aid of which we solve (6.5) with the corresponding boundary conditions, using (6.14). The coefficients (6.15) of (6.14) are computed using the functions from the BSEq class.
(5) Here we compute the $v_{i, j}$ using the explicit method. This is the main task of our program.
6 We display the price $v(0, S(0))$.
(7) In order for our method to work we need to subdivide the time interval $[0, T]$ into a large number of parts. This is connected with the numerical stability of the method. For small $i_{\max }$, errors can accumulate and blow up to produce invalid results. For the method to be stable, $\frac{\Delta t}{\Delta x^2}$ has to be sufficiently small.
Once we have computed the $v_{i, j}$, we can use (6.13) to approximate $\frac{\partial v\left(t_i, x_j\right)}{\partial x}$. This means that we can compute the replicating strategy using deltahedging.
*/

int main()
{
   double S0=100.0, r=0.05, sigma=0.2;
   BSModel Model(S0,r,sigma);

   double K=100.0, T=1./12., zl=0.0, zu=2.0*S0;
   Put EuropeanPut(K,T,zl,zu);

   BSEq BSPDE(&Model,&EuropeanPut);

   int imax=3000, jmax=1000;
   ExplicitMethod Method(&BSPDE, imax, jmax);

   Method.SolvePDE();

   cout << "Price = " << Method.v(0.0,S0) << endl;

   return 0;
}
