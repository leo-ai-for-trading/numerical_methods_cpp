#include "BinModel02.h"
#include "Options06.h"
#include <iostream>
#include <cmath>
using namespace std;
/*
A virtual function with no definition as indicated by =0 
is called a pure virtual function, and the class containing 
it is called an abstract class.
We have the abstract concept of European option represented 
by the abstract EurOption class
Bear in mind that when a class contains a pure virtual function, 
it is impossible to declare an object of that class
*/
int main() {
   BinModel Model;
   if (Model.GetInputData()==1) return 1;
   Call Option1;
   Option1.GetInputData();
   cout << "European call option price = "
        << Option1.PriceByCRR(Model)
        << endl << endl;
   Put Option2;
   Option2.GetInputData();
   cout << "European put option price = "
        << Option2.PriceByCRR(Model)
        << endl << endl;
return 0; 
}
