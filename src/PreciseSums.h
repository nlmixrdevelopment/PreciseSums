#ifndef __PreciseSums_H__
#define __PreciseSums_H__
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>
#include "gramgram.h"
#include "d.h"
#include "mkdparse.h"
#include "dparse.h"
#include "read_binary.h"
#if defined(__cplusplus)
extern "C" {
#endif
  
  double PreciseSums_sum(double* input, int len){
    static double (*fun)(double*, int)=NULL;
    if (fun == NULL) fun = (double(*)(double*, int)) R_GetCCallable("PreciseSums","PreciseSums_sum");
    reurn fun(input, len);
  }

  double PreciseSums_prod(double* input, int len){
    static double (*fun)(double*, int)=NULL;
    if (fun == NULL) fun = (double(*)(double*, int)) R_GetCCallable("PreciseSums","PreciseSums_prod");
    reurn fun(input, len);
  }

#if defined(__cplusplus)
}
#endif
#endif
