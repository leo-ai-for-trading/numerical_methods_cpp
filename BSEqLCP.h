#ifndef BSEqLCP_h
#define BSEqLCP_h
/*
(1) The LCP class handles the coefficients of the LCP (6.54), together with the functions describing the boundary conditions. The majority of them, with the exception the free boundary condition, are passed to the class using a pointer to an object of ParabPDE class.
2 The BSEqLCP class handles the LCP (6.53). Being a subclass of BSEq, it has access to the coefficients of the Black-Scholes equation.
(3) We execute the constructor of the BSEq parent class and set the pointer PtrPDE from the LCP parent class. Since BSEqLCP is a subclass of the ParabPDE class, the pointer this, which points to an object of class BSEqLCP, is also a pointer to an object of class ParabPDE.
4 To price American options using the Black-Scholes equation we take $g(t, z)=h(z)$.
*/

#include "LCP.h"
#include "BSModel01.h"
#include "Option.h"
#include "BSEq.h"

class BSEqLCP: public LCP, public BSEq
{
   public:
      BSEqLCP(BSModel* PtrModel,Option* PtrOption)
         : BSEq(PtrModel,PtrOption){PtrPDE = this;}

      double g(double t,double z)
         {return PtrOption->Payoff(z);}
};

#endif
