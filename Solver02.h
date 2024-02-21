#ifndef Solver02_h
#define Solver02_h
/*
An abstract class called Function is introduced to represent a general
function f . The class has two pure virtual member functions: Value()
to return the value of f at x, and Deriv() to return the value of the ′
derivative f at x.
Fct is passed to SolveByBisect() and SolveByNR() no longer as a function pointer but as a pointer to the Function class. We need to work with a pointer to this class to take advantage of virtual functions.
DFct, the function pointer passed to SolveByNR() in the previous version to compute the derivative is no longer needed. Deriv() is now a member of the Function class, and both Value() and Deriv() can be accessed through the pointer Fct to this class.
For example, Fct->Value(x_prev) returns the value of the func- tion at x_prev, and Fct->Deriv(x_prev) returns the derivative at x_prev.
Note the operator ->. It should be used when a function that is a member of a class is called with a pointer to an object of that class (or a subclass).
*/


class Function
{
   public:
      virtual double Value(double x)=0;
      virtual double Deriv(double x)=0;
};
double SolveByBisect(Function* Fct,
   double Tgt, double LEnd, double REnd, double Acc)

{
   double left=LEnd, right=REnd, mid=(left+right)/2;
   double y_left=Fct->Value(left)-Tgt, y_mid=Fct->Value(mid)-Tgt;
   while (mid-left>Acc)
   {
if ((y_left>0 && y_mid>0)||(y_left<0 && y_mid<0))
         {left=mid; y_left=y_mid;}
      else right=mid;
      mid=(left+right)/2;
      y_mid=Fct->Value(mid)-Tgt;
}
return mid; }
double SolveByNR(Function* Fct,
   double Tgt, double Guess, double Acc)
{
   double x_prev=Guess;
   double x_next=x_prev
      -(Fct->Value(x_prev)-Tgt)/Fct->Deriv(x_prev);
   while (x_next-x_prev>Acc || x_prev-x_next>Acc)
   {
      x_prev=x_next;
      x_next=x_prev
         -(Fct->Value(x_prev)-Tgt)/Fct->Deriv(x_prev);
}
   return x_next;
}
#endif