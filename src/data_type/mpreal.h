#include <iostream>
#include <mpreal.h>
#include <dlmalloc.h>

#define ODE_REAL mpreal

using namespace mpfr;
using namespace std;

#define ODE_INIT()				\
  {						\
    mpreal::set_default_prec(1000);		\
    cout.precision(15);				\
  }

#define ODE_RP(r) cout << r
