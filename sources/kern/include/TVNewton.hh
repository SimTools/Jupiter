#ifndef __TVNEWTON__
#define __TVNEWTON__
//*****************************************************************************
//* --------------
//* class TVNewton
//* --------------
//*
//* (Purpose)
//*   A simple base class to solve
//*      F(x) = 0
//*   using Newton's Method.
//*
//* (Dependency)
//*   Requires: no libraries
//*   Provides: TVNewton
//*
//* (Usage)
//*   Implement the following pure virtuals:
//*       F   (x): function 
//*       DFdx(x): its 1st derivative
//*   in the derived class, say, Solver, as
//*
//*       class Solver : public TVNewton {
//*          public:
//*             Solver(double x) : TVNewton(x) {}
//*             double F   (double x) { return x*(x+1); }
//*             double DFdx(double x) { return 2*x+1;   }
//*       };
//*
//*   and use it as
//*
//*       Solver sol(1.);         // create solver with initial value 1.
//*       double x = sol.Solve(); // this is the solution.
//*
//*   In this simple example, the solution should be very close to 0,
//*   as you can expect from the function form: F(x) = x*(x+1).
//*   Notice that you would get x = -1, if you start from, say, -4.
//*
//* (Update Record)
//*   2004/08/01  K.Fujii  Primitive version.
//*
//*****************************************************************************

#include <cmath>

class TVNewton {
  public:
     TVNewton(double x = 0.     /* initial value of x          */,
              double e = 1.e-12 /* tolerance: OK if |F(x)| < e */)
          : fXcurr(x), fCurr(1.e+20), fEpsilon(e), fLambda(1.) {}

     virtual ~TVNewton() {}

     virtual double F   (double x) = 0;
     virtual double DFdx(double x) = 0;

     double  Solve()
     {
        fCurr = F(fXcurr);
        fXcurr       -= fCurr/(DFdx(fXcurr)*(1.+fLambda));
        double fnext  = F(fXcurr);
        if (std::fabs(fnext) <= fEpsilon ) return fXcurr;

        if (std::fabs(fnext) > std::fabs(fCurr)) fLambda *= 10.;
        else                           fLambda /= 10.;
        fCurr = fnext;
        return Solve();
     }

  private:
     double fXcurr;
     double fCurr;
     double fEpsilon;
     double fLambda;
};
#endif
