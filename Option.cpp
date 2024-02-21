#include "Option.h"
#include <cmath>
/*
(1) This is the file from Listing 5.1. Not all functionality in this class, for example GenereateRandPath(), is needed in the present chapter.
(2) The Option class includes virtual functions for the payoff and boundary conditions.
3 We declare $\mathrm{T}, \mathrm{zu}$, and $\mathrm{zl}$ as public in order to streamline the code and save space. These variables should be declared as private and introduced together with the corresponding public access functions. In this chapter we are going to cut many such corners in order to keep the code as short and transparent as possible.
4 A boundary condition often uses some parameters of the model. These will be passed using a pointer to an object of class BSModel containing these parameters.
(5) This is the payoff of the put $h^{\text {put }}(z)=(K-z)^{+}$.
6 Here we have the upper boundary condition (6.7).
(7) The lower boundary condition is given by (6.8).
Now we introduce a general class for handling the coefficients of (6.1) and for the functions describing the boundary conditions, together with a subclass where we implement (6.5).

The class structure is depicted in Figure 6.1. 
In the diagram we find two relationships between classes. 
The one designated by an arrow represents the 'is a' 
relationship. For example, the Black-Scholes equation is a 
parabolic partial differential equation. 
The other one, depicted by a rhombus, represents the 'has a' relationship. The diagram indicates that BSEq has a pointer to Option and a pointer to BSModel among its members.
*/

double Put::Payoff(double z)
{
   if (K<z) return 0.0;
   return K-z;
}

double Put::UpperBdCond(BSModel* PtrModel, double t)
{
   return 0.0;
}

double Put::LowerBdCond(BSModel* PtrModel, double t)
{
   return K*exp(-PtrModel->r*(T-t));
}
