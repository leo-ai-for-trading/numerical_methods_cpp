#include "FDMethod.h"
/*
(1) The class ParabPDE from Listing 6.3 holds the coefficients $a(t, x)$, $b(t, x), c(t, x)$ and $d(t, x)$ of (6.1). Based on these, the values $a_{i, j}, b_{i, j}, c_{i, j}$ and $d_{i, j}$ will be computed. ParabPDE also contains the boundary conditions, which will be used to compute $f_j, f_{l, i}$ and $f_{u, i}$.
(2) PtrPDE will be used to pass the functions from the ParabPDE class.
$3 \mathrm{v}$ is a matrix (declared as a vector of vectors) which will store the $v_{i, j}$ from (6.10).
$4 \mathrm{t}$ (i) and $\mathrm{x}(\mathrm{j})$ return $t_i$ and $x_j$, respectively, using (6.9).
(5) These functions return $a_{i, j}, b_{i, j}, c_{i, j}$ and $d_{i, j}$ using (6.11). Note that we declare $i$ as double. This is done intentionally, since having fractional $i$ will allow us to refine the method later on.
$6 f_j, f_{l, i}$ and $f_{u, i}$ are computed from (6.12).
$\left(0\right.$ Based on $v_{i, j}$, we can compute $v(t, x)$ for arbitrary $t \in[0, T]$ and $x \in$ $\left[x_l, x_u\right]$ using linear interpolation. This will be the task of the function $\mathrm{v}(\mathrm{)}$.
8 We compute $\Delta x$ and $\Delta t$ using (6.9).
(9 $\mathrm{v}$ is resized to be an $\left(i_{\max }+1\right) \times\left(j_{\max }+1\right)$ matrix.
(10) We choose $i, j$ to represent a grid point approximating the given $t \in$ $\left[t_i, t_{i+1}\right]$ and $x \in\left[x_j, x_{j+1}\right]$.
(1) We find weights $\lambda_0, \lambda_1$ and $\omega_0, \omega_1$ such that $\lambda_0+\lambda_1=\omega_0+\omega_1=1$ and (see Figure 6.3)
$$
\begin{aligned}
& t=\lambda_0 t_i+\lambda_1 t_{i+1}, \\
& x=\omega_0 x_j+\omega_1 x_{j+1} .
\end{aligned}
$$
*/

FDMethod::FDMethod(ParabPDE* PtrPDE_, int imax_, int jmax_)
{
   PtrPDE=PtrPDE_;
   imax=imax_; jmax=jmax_;
   dx=(PtrPDE->xu - PtrPDE->xl)/jmax;
   dt=PtrPDE->T/imax;
   V.resize(imax+1);
   for (int i=0; i<=imax; i++) V[i].resize(jmax+1);
}

double FDMethod::v(double t,double x)
{
   int i = (int)(t/dt);
   int j = (int)((x-PtrPDE->xl)/dx);
   double l1 = (t-FDMethod::t(i))/dt, l0 = 1.0-l1;
   double w1 = (x-FDMethod::x(j))/dx, w0 = 1.0-w1;
   return l1*w1*V[i+1][j+1] + l1*w0*V[i+1][j]
         +l0*w1*V[ i ][j+1] + l0*w0*V[ i ][j];
}
