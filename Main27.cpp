#include <iostream>
#include "BSModel01.h"
#include "Option.h"
#include "BSEqLCP.h"
#include "ExplicitLCP.h"
/*
(1) This class stores the coefficients of a discretised LCP.
(2) The pointer PtrLCP is used to gain access to the function $g(t, x)$ from the LCP class.
3 We need the pointer PtrFDMethod to access the members of the FDMethod class.
(4) We compute $g_{i, j}=g\left(t_i, x_j\right)$ using the function $\mathrm{g}()$ from the LCP class, together with the functions $t(), \mathrm{x}()$ from the FDMethod class.
(5) The coefficients $A_{i, j}, B_{i, j}, C_{i, j}$ and $D_{i, j}$ of the discretised LCP (6.56) are computed from the same formulae as those of the explicit method. To gain access to them we make ExplicitLCP a subclass of the class ExplicitMethod. Making ExplicitLCP also a subclass of the FDLCP class gives access to the coefficient $g_{i, j}$.
6 We execute the constructor of the ExplicitMethod class using the pointer PtrLCP_->PtrPDE.
0 We set the pointer PtrLCP from the FDLCP parent class.
8 To set the pointer PtrFDMethod from the FDLCP parent class we use the same technique which was used for the LCP and BSEqLCP classes.
$\left(9\right.$ This function implements the method, and computes the $v_{i, j}$.
(10) The function SolveLCP () is very similar to SolvePDE () from Listing 6.9.
(1) We compute $v_{i_{\max }, j}$ from the terminal boundary condition (6.57).
(12) This loop ensures that we apply (6.58) instead of (6.14), and that we compute the lower and upper boundary conditions using (6.57).

All that remains is to put the ingredients together inside the main () function.
*/
int main()
{
   double S0=100.0, r=0.05, sigma=0.2;
   BSModel Model(S0,r,sigma);

   double K=100.0, T=1./12., zl=0.0, zu=2.0*S0;
   Put PutOption(K,T,zl,zu);

   BSEqLCP BSLCP(&Model,&PutOption);

   int imax=3000, jmax=1000;
   ExplicitLCP Method(&BSLCP, imax, jmax);

   Method.SolveLCP();
   cout << "Am  Put Price = " << Method.v(0.0,S0) << endl;

   Method.SolvePDE();
   cout << "Eur Put Price = " << Method.v(0.0,S0) << endl;

   return 0;
}
