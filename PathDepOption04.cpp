#include "PathDepOption04.h"
#include <cmath>
/*
- This is the pricing function in which we compute H(0) using (5.17). CVOption plays the role of control variate.
- Options that can be used as control variates need to have an analytic pricing formula. Here we add a function in which we compute G(0) from the Black–Scholes formula. We make this function virtual, since the formula may vary depending on the type of option.
-Not all path-dependent options can be priced analytically. Here we re- turn 0.0 to allow for having a subclass of PathDepOption without a PriceByBSFormula() function.
-We add a class which combines two options with payoffs H(T) and G(T ), and creates an option with payoff H(T ) − G(T ).
Pointers Ptr1 and Ptr2 refer to options with payoffs H(T ) and G(T ), respectively.
-ThepayoffisequaltoH(T)−G(T).
- We initialise an object VarRedOpt of class DifferenceOfOptions. The keyword this requires careful explanation. When an object of some class is used, then this appearing anywhere inside that class des- ignates a pointer to that object. Here the pointer this appears inside the PathDepOption class (or more precisely, inside a function belonging to that class). Later on, inside the main() function in Listing 5.14, we
will have an object Option declared by
ArthmAsianCall Option(T,K,m);
Because ArthmAsianCall is a subclass of the PathDepOption class, Option can be regarded as an object of the parent class. When Option.PriceByVarRedMC(Model,N,CVOption);
is executed, the this pointer inside PriceByVarRedMC() will there- fore be pointing to the Option object. When it is passed to the con- structor function of the VarRedOpt class in
DifferenceOfOptions VarRedOpt(T,m,this,&CVOption); the Payoff() function in the VarRedOpt class will produce the differ-
ence between the payoffs of Option and CVOption.
- We compute H(0) using (5.17). By calling VarRedOpt.PriceByMC(), e−rT E∗(H(T) − G(T)) is computed using Monte Carlo. Then G(0) is computed in CVOption.PriceByBSFormula() from an analytic for- mula.
- Since G(0) is computed analytically, the only source of error follows from the Monte Carlo computation of e−rT E∗(H(T ) − G(T )).
*/
double PathDepOption::PriceByMC(BSModel Model, long N)
{
   double H=0.0, Hsq=0.0;
   SamplePath S(m);
   for(long i=0; i<N; i++)
   {
      Model.GenerateSamplePath(T,m,S);
      H = (i*H + Payoff(S))/(i+1.0);
      Hsq = (i*Hsq + pow(Payoff(S),2.0))/(i+1.0);
   }
   Price = exp(-Model.r*T)*H;
   PricingError = exp(-Model.r*T)*sqrt(Hsq-H*H)/sqrt(N-1.0);
   return Price;
}
double PathDepOption::PriceByVarRedMC
       (BSModel Model, long N, PathDepOption& CVOption)
{
   DifferenceOfOptions VarRedOpt(T,m,this,&CVOption);
   Price = VarRedOpt.PriceByMC(Model,N)
           + CVOption.PriceByBSFormula(Model);
   PricingError = VarRedOpt.PricingError;
   return Price;
}
double ArthmAsianCall::Payoff(SamplePath& S)
{
   double Ave=0.0;
   for (int k=0; k<m; k++) Ave=(k*Ave+S[k])/(k+1.0);
   if (Ave<K) return 0.0;
   return Ave-K;
}