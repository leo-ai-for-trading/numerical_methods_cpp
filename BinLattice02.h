#ifndef BinLattice02_h
#define BinLattice02_h
#include <iostream>
#include <iomanip>
#include <vector>
//Type sostituisce i tipi dei vettori o delle variabili
/*
A class tem- plate can only be compiled after an object has been declared using the template with a specific data type, for example double, substituted for the type parameter, and we have not done so yet. Separate compilation will not work for them.
*/
using namespace std;
template<typename Type> class BinLattice
{
private:
      int N;
      vector< vector<Type> > Lattice;
   public:
      void SetN(int N_)
      {
         N=N_;
         Lattice.resize(N+1);
         for(int n=0; n<=N; n++) Lattice[n].resize(n+1);
      }
      void SetNode(int n, int i, Type x)
         {Lattice[n][i]=x;}
      Type GetNode(int n, int i)
         {return Lattice[n][i];}
      void Display()
      {
         cout << setiosflags(ios::fixed)
              << setprecision(3);
         for(int n=0; n<=N; n++)
         {
            for(int i=0; i<=n; i++)
               cout << setw(7) << GetNode(n,i);
            cout << endl;
         }
         cout << endl;
      }
}; 
#endif