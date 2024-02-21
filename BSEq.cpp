#include "BSEq.h"
#include <cmath>
/*
(1) The ParabPDE class consists of virtual functions for the coefficients of (6.1) and for the functions describing the boundary conditions. It also contains $\mathrm{T}, \mathrm{xl}, \mathrm{xu}$, which specify the domain $[0, T] \times\left[x_l, x_u\right]$.
2 The class BSEq stores the coefficients and boundary conditions of the Black-Scholes equation (6.5).
(3) PtrModel will be used to pass the parameters of the model to the functions.
(4) The boundary conditions of BSEq will be computed based on the boundary conditions of the option pointed to by Ptroption.
(5) In the constructor we pass the pointers to the classes and initialise $T, x_l, x_u$.
6 Here we have the coefficients (6.6) of the Black-Scholes equation.
$(7$ The boundary conditions are obtained from those of the option.
*/

BSEq::BSEq(BSModel* PtrModel_,Option* PtrOption_)
{
   PtrModel=PtrModel_; PtrOption=PtrOption_;
   T =PtrOption->T;
   xl=PtrOption->zl;
   xu=PtrOption->zu;
}

double BSEq::a(double t, double z)
{
   return -0.5*pow(PtrModel->sigma*z,2.0);
}

double BSEq::b(double t, double z)
{
   return -PtrModel->r*z;
}

double BSEq::c(double t, double z)
{
   return PtrModel->r;
}

double BSEq::d(double t, double z)
{
   return 0.0;
}

double BSEq::f(double z)
{
   return PtrOption->Payoff(z);
}

double BSEq::fl(double t)
{
   return PtrOption->LowerBdCond(PtrModel,t);
}

double BSEq::fu(double t)
{
   return PtrOption->UpperBdCond(PtrModel,t);
}
