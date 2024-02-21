#include "ImplicitScheme.h"
#include "Matrix.h"
#include <cmath>
/*
(1) These functions return $A_{i, j}, \ldots, G_{i, j}$. The scheme does not depend on the choice of the coefficients, hence we leave these functions as virtual.
2 w (i) returns $\mathbf{w}_i$ from (6.35).
3 A (i, q) returns $\mathbf{A}_i \mathbf{q}$ for $\mathbf{A}_i$ defined in (6.24).
6.3 Implicit schemes
147
4 LuDecomposition (i, q) computes $\mathbf{B}_i^{-1} \mathbf{q}$ using Lemma 6.1.
(5) SolvePDE ( ) is the function in which we compute the $v_{i, j}$ using (i)-(iii).
6 This is the file from Listing 5.15. For our program we only need the operator + between two vectors. The operator is used in SolvePDE ( ) for the computation of $\mathbf{A}_i \mathbf{v}_i+\mathbf{w}_i$.
(7) We declare the vectors to be of dimension $j_{\max }+1$, rather than $j_{\max }-1$ as is in (6.37). There are two reasons for doing so. Firstly, this way we have compatibility of dimension with V [i] in SolvePDE ( ). Secondly, this allows us to use the same indices in the code as in our formulae, which makes implementation more transparent. In all matrix operations needed for (6.37) we simply ignore the first coordinate $j=0$ and the last coordinate $j=j_{\max }$ of the vectors involved.
8 The vectors $\mathbf{r}, \mathbf{y}$ are computed inductively using (6.40).
(9) The vector $\mathbf{p}=\mathbf{B}_i^{-1} \mathbf{q}$ is computed using (6.41).
(10) We apply (6.36) to compute $\mathbf{v}_{i_{\max }}$.
(1) We use (6.37) to compute $\mathbf{v}_{i-1}$.
(12) We compute $v_{i, 0}$ and $v_{i, j_{\max }}$ using (6.31) and (6.32), respectively.

We now write out a class containing the coefficients (6.29) of the CrankNicolson method and then put the classes to work in the main () function.
*/
Vector ImplicitScheme::w(int i)
{
   Vector w(jmax+1);
   w[1]=D(i,1)+A(i,1)*fl(i)-E(i,1)*fl(i-1);
   for (int j=2;j<jmax-1;j++) w[j]=D(i,j);
   w[jmax-1]=D(i,jmax-1)+C(i,jmax-1)*fu(i)-G(i,jmax-1)*fu(i-1);
   return w;
}

Vector ImplicitScheme::A(int i, Vector q)
{
   Vector p(jmax+1);
   p[1]=B(i,1)*q[1]+C(i,1)*q[2];
   for (int j=2;j<jmax-1;j++)
   {
      p[j]=A(i,j)*q[j-1]+B(i,j)*q[j]+C(i,j)*q[j+1];
   }
   p[jmax-1]=A(i,jmax-1)*q[jmax-2]+B(i,jmax-1)*q[jmax-1];
   return p;
}

Vector ImplicitScheme::LUDecomposition(int i, Vector q)
{
   Vector p(jmax+1), r(jmax+1), y(jmax+1);
   r[1]=F(i,1);
   y[1]=q[1];
   for (int j=2;j<jmax;j++)
   {
      r[j]=F(i,j)-E(i,j)*G(i,j-1)/r[j-1];
      y[j]=q[j]-E(i,j)*y[j-1]/r[j-1];
   }
   p[jmax-1]=y[jmax-1]/r[jmax-1];
   for (int j=jmax-2; j>0; j--)
   {
      p[j]=(y[j]-G(i,j)*p[j+1])/r[j];
   }
   return p;
}

void ImplicitScheme::SolvePDE()
{
   for (int j=0; j<=jmax; j++) V[imax][j]=f(j);
   for (int i=imax; i>0; i--)
   {
      V[i-1]=LUDecomposition(i,A(i,V[i])+w(i));
      V[i-1][0]=fl(i-1);
      V[i-1][jmax]=fu(i-1);
   }
}
