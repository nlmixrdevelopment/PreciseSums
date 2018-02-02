#ifndef __PreciseSums_H__
#define __PreciseSums_H__

#define PS_DoubleSum 5
#define PS_PairwiseSum 1
#define PS_FSum 2
#define PS_KahanSum 3
#define PS_NeumaierSum 4

#define PS_ProdLD 1
#define PS_Prod 2
#define PS_LogifyProd 3

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>
#if defined(__cplusplus)
extern "C" {
#endif
  
  double PreciseSums_sum(double* input, int len){
    static double (*fun)(double*, int)=NULL;
    if (fun == NULL) fun = (double(*)(double*, int)) R_GetCCallable("PreciseSums","PreciseSums_sum");
    return fun(input, len);
  }

  double PreciseSums_prod(double* input, int len){
    static double (*fun)(double*, int)=NULL;
    if (fun == NULL) fun = (double(*)(double*, int)) R_GetCCallable("PreciseSums","PreciseSums_prod");
    return fun(input, len);
  }
  
  double PreciseSums_prod_r(double *input, double *p, int n, int type){
    static double (*fun)(double*, double*, int, int)=NULL;
    if (fun == NULL) fun = (double(*)(double*, double*, int, int)) R_GetCCallable("PreciseSums","PreciseSums_prod_r");
    return fun(input, p, n, type);
  }

  double PreciseSums_sum_r(double *input, int n, long double *p, int m, int type){
    static double (*fun)(double *, int, long double *, int, int)=NULL;
    if (fun == NULL) fun = (double(*)(double *, int, long double *, int, int)) R_GetCCallable("PreciseSums","PreciseSums_sum_r");
    return fun(input, n, p, m, type);
  }
  
#if defined(__cplusplus)
}
#endif
#endif
