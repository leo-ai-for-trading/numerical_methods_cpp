#ifndef Option02_h
#define Option02_h

//input and displaying option data
int GetInputData(int* PtrN, double* Ptrk);

//pricing European Option
double PriceByCRR(double S0, double U,double D,
                double R,int N, double K);

//computing call payoff
double CallPayoff(double z, double K);

#endif