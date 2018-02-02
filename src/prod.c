#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h> //Rmath includes math.

extern double PreciseSums_sum (double *input, int n);

extern double PreciseSums_pairwise_add_DOUBLE(double *a, int n);

double PreciseSums_safe_log(double x){
  if (x <= 0){
    // Warning?
    return log(DOUBLE_EPS);
  } else {
    return log(x);
  }
}

int PreciseSums_prod_type = 3;

extern void PreciseSums_prod_set(int i){
  PreciseSums_prod_type = i;
}

extern int PreciseSums_prod_get(){
  return PreciseSums_prod_type;
}


SEXP _psSetProd(SEXP input){
  PreciseSums_prod_type = (int) INTEGER(input)[0];
  return R_NilValue;
}

extern double PreciseSums_prod_ld(double *input, int n){
  long double p = 1;
  for  (int i = 0; i < n; i++){
    if (input[i] == 0){
      return 0.0; 
    }
    p *= input[i];
  }
  return (double)p;
}

extern double PreciseSums_prod_d(double *input, int n){
  double p = 1;
  for  (int i = 0; i < n; i++){
    if (input[i] == 0){
      return 0.0; 
    }
    p *= input[i];
  }
  return p;
}

extern double PreciseSums_prod_logify_r(double *input, double *p, int n){
  double s = 1.0;
  for (int i = 0; i < n; i++){
    if (input[i] == 0){
      return 0.0;
    }
    s = sign(input[i])*s;
    p[i] = PreciseSums_safe_log(fabs(input[i]));
  }
  s = exp(PreciseSums_pairwise_add_DOUBLE(p, n))*s;
  return s;
}

extern double PreciseSums_prod_logify(double *input, int n){
  double *p = Calloc(n,double);
  double ret= PreciseSums_prod_logify_r(input, p, n);
  Free(p);
  return ret;
}




extern double PreciseSums_prod_r(double *input, double *p, int n, int type){
  switch (type){
  case 1: // long double multiply, then convert back.
    return PreciseSums_prod_ld(input, n);
    break;
  case 2: // simple double multiply
    return PreciseSums_prod_d(input, n);
    break;
  case 3: // logify
    return PreciseSums_prod_logify_r(input, p, n);
  }
  return 0.0;
}

extern double PreciseSums_prod(double *input, int n){
  switch (PreciseSums_prod_type){
  case 1: // long double multiply, then convert back.
    return PreciseSums_prod_ld(input, n);
    break;
  case 2: // simple double multiply
    return PreciseSums_prod_d(input, n);
    break;
  case 3: // logify
    return PreciseSums_prod_logify(input, n);
  }
  return 0.0;
}



SEXP _psProd(SEXP input){
  int len = length(input);
  double *dinput = REAL(input);
  SEXP rets = PROTECT(allocVector(REALSXP,1));
  REAL(rets)[0] = PreciseSums_prod(dinput, len);
  UNPROTECT(1);
  return rets;
}

extern double PreciseSums_prodV(int n, ...){
  va_list valist;
  va_start(valist, n);
  double *p = Calloc(n, double);
  for (int i = 0; i < n; i++){
    p[i] = va_arg(valist, double);
  }
  va_end(valist);
  double s = PreciseSums_prod(p, n);
  Free(p);
  return s;
}

extern double PreciseSums_prodV_r(double *p, int n, ...){
  va_list valist;
  va_start(valist, n);
  for (int i = 0; i < n; i++){
    p[i] = va_arg(valist, double);
  }
  va_end(valist);
  double s = PreciseSums_prod(p, n);
  return s;
}


extern double PreciseSums_signV(int n, ...){
  va_list valist;
  va_start(valist, n);
  double s = 1;
  for (int i = 0; i < n; i++){
    s = sign(va_arg(valist, double))*s;
    if (s == 0){
      break;
    }
  }
  va_end(valist);
  return s;
}
