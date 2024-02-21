#ifndef Solver01_h
#define Solver01_h
/*
The function SolveByBisect() is defined to implement the bisection method.
It takes a function pointer Fct as an argument, so a function f can be passed to the solver
In addition, SolveByBisect() takes arguments Tgt for the target value c of the function, 
LEnd and REnd for the left and right endpoints of the interval [a, b], 
and Acc for the desired accuracy of the numerical solution, which will determine when the algorithm should be stopped.
Care is taken in SolveByBisect() that only one evaluation of f is made for each loop iteration in order to speed up computation. This results in slightly more complicated code than may seem necessary, namely the introduction of the variables y_left and y_mid to carry values of the function between loop iterations. The price is worth paying because the bisection method is not lightning fast.
Checking whether or not f (a) − c, f (b) − c have opposite signs to begin with is omitted in SolveByBisect() for simplicity. 
*/
double SolveByBisect(double(*Fct)(double x),
   double Tgt, double LEnd, double REnd, double Acc)
{
   double left=LEnd, right=REnd, mid=(left+right)/2;
   double y_left=Fct(left)-Tgt, y_mid=Fct(mid)-Tgt;
   while (mid-left>Acc)
   {
      if ((y_left>0 && y_mid>0)||(y_left<0 && y_mid<0))
         {left=mid; y_left=y_mid;}
      else right=mid;
      mid=(left+right)/2;
      y_mid=Fct(mid)-Tgt;
   }
return mid; 
}
/*
SolveByNR() implements the Newton–Raphson solver.
It takes two function pointers Fct and DFct so that both a function f and its derivative
can be passed. Moreover, SolveByNR() also takes arguments Tgt for the target value c, Guess for the initial term x0 of
the approximating sequence, and Acc for the desired accuracy to be reached before the algorithm is terminated.
The iterations xn will converge to an x such that f (x) = c 
if f ′(x) != 0 and x0 is close enough to x. 
In this case the algorithm will be termi- nated after the prescribed accuracy is reached. In other circumstances SolveByNR() may enter an infinite loop. 
This ought to be prevented, for example by setting an upper limit on the number of iterations, but it is not, for simplicity.
*/
double SolveByNR(double(*Fct)(double x),
   double(*DFct)(double x),
   double Tgt, double Guess, double Acc)
{
   double x_prev=Guess;
   double x_next=x_prev-(Fct(x_prev)-Tgt)/DFct(x_prev);
   while (x_next-x_prev>Acc || x_prev-x_next>Acc)
   {
      x_prev=x_next;
      x_next=x_prev-(Fct(x_prev)-Tgt)/DFct(x_prev);
   }
   return x_next;
}
#endif