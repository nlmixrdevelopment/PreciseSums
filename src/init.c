#include <stdio.h>
#include <stdlib.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h> //Rmath includes math.
#include <R_ext/Rdynload.h>

SEXP _psKahanSum(SEXP input);
SEXP _psNeumaierSum(SEXP input);

SEXP _psPythonSum(SEXP input);
SEXP _psProd(SEXP input);
SEXP _psSum(SEXP input);
SEXP _psSetSum(SEXP input);
SEXP _psSetProd(SEXP input);
SEXP _psPairwiseSum(SEXP input);
double PreciseSums_sum(double *input, int len);
double PreciseSums_prod(double *input, int len);

static R_NativePrimitiveArgType PreciseSums_Sum_t[] = {
  REALSXP, INTSXP
};


void R_init_PreciseSums(DllInfo *info){
  R_CallMethodDef callMethods[]  = {
    {"_psKahanSum", (DL_FUNC) &_psKahanSum,1},
    {"_psNeumaierSum", (DL_FUNC) &_psNeumaierSum,1},
    {"_psPythonSum", (DL_FUNC) &_psPythonSum, 1},
    {"_psPairwiseSum", (DL_FUNC) &_psPairwiseSum, 1},
    {"_psSum", (DL_FUNC) &_psSum, 1},
    {"_psProd", (DL_FUNC) &_psProd, 1},
    {"_psSetSum",(DL_FUNC) &_psSetSum, 1},
    {"_psSetProd",(DL_FUNC) &_psSetProd, 1},
    {NULL, NULL, 0}
  };
  
  R_RegisterCCallable("PreciseSums","PreciseSums_sum",              (DL_FUNC) PreciseSums_sum);
  R_RegisterCCallable("PreciseSums","PreciseSums_prod",             (DL_FUNC) PreciseSums_prod);
  
  static const R_CMethodDef cMethods[] = {
    {"PreciseSums_sum", (DL_FUNC) &PreciseSums_sum, 2, PreciseSums_Sum_t},
    {"PreciseSums_prod", (DL_FUNC) &PreciseSums_prod, 2, PreciseSums_Sum_t},
    {NULL, NULL, 0, NULL}
  };
  
  R_registerRoutines(info, cMethods, callMethods, NULL, NULL);
  R_useDynamicSymbols(info, FALSE);

}
