#' Using the Kahan method, take a more accurate sum
#'
#' @param numbers A vector of numbers to sum.
#' @return Sum of numbers
#' @references
#' \url{https://en.wikipedia.org/wiki/Kahan_summation_algorithm}
#' @examples
#' sum(c(1,1e100,1,-1e100)) ## Should be 2, gives 0
#' kahanSum(c(1,1e100,1,-1e100)) ## Not accurate enough for the correct result. (still = 0)
#' @export
kahanSum <- function(numbers) {
    .Call(`_psKahanSum`, as.double(numbers))
}

#' Using the Neumaier method, take a more accurate sum
#'
#' @inheritParams kahanSum
#' @return Sum of numbers, a bit more accurate than kahanSum
#' @references
#' \url{https://en.wikipedia.org/wiki/Kahan_summation_algorithm}
#' @examples
#' sum(c(1,1e100,1,-1e100)) ## Should be 2, gives 0
#' neumaierSum(c(1,1e100,1,-1e100)) ## Gives 2
#' @export
neumaierSum <- function(numbers) {
    .Call(`_psNeumaierSum`, as.double(numbers))
}

#' Return an accurate floating point sum of values
#'
#' This method avoids loss of precision by tracking multiple
#' intermediate partial sums. Based on python's math.fsum
#'
#' @inheritParams kahanSum
#'
#' @return Sum of numbers without loss of precision
#'
#' The algorithm's accuracy depends on IEEE-754 arithmetic guarantees
#' and the typical case where the rounding mode is half-even. On some
#' non-Windows builds, the underlying C library uses extended
#' precision addition and may occasionally double-round an
#' intermediate sum causing it to be off in its least significant bit.
#'
#' @export
#' @author Matthew Fidler (R implementation), Raymond Hettinger,
#'     Jonathan Shewchuk, Python Team
#' @references
#'
#' \url{https://docs.python.org/2/library/math.html}
#'
#' \url{https://code.activestate.com/recipes/393090/}
#'
#' \url{https://github.com/python/cpython/blob/a0ce375e10b50f7606cb86b072fed7d8cd574fe7/Modules/mathmodule.c}
#'
#' Shewchuk, JR. (1996)
#' \emph{Adaptive Precision Floating-Point Arithmetic and Fast Robust Geometric Predicates.}
#' \url{http://www-2.cs.cmu.edu/afs/cs/project/quake/public/papers/robust-arithmetic.ps}
#' @examples
#' sum(c(1,1e100,1,-1e100)) ## Should be 2, gives 0
#' fsum(c(1,1e100,1,-1e100)) ## Gives 2.
#'
fsum <- function(numbers) {
    .Call(`_psPythonSum`, as.double(numbers))
}

#' Return an accurate floating point sum of values
#'
#' This was taken by NumPy and adapted for use here.  It is more
#' accurate than a standard sum, but still has numerical issues.  Its
#' main benefit is that it is about the same amount of time as a
#' standard time with the added accuracy.
#'
#' @inheritParams kahanSum
#'
#' @return A sum of numbers with a rounding error of O(lg n) instead
#'     of O(n).
#' @author Matthew Fidler (R implementation), Julian Taylor, Nathaniel
#'     J Smith, and  NumPy team.
#' #' @examples
#' sum(c(1,1e100,1,-1e100)) ## Should be 2, gives 0
#' pairwiseSum(c(1,1e100,1,-1e100)) ## Should be 2, still 0
#' @export
#' @references
#' \url{https://github.com/juliantaylor/numpy/blob/b0bc01275cac04483e6df021211c1fa2ba65eaa3/numpy/core/src/umath/loops.c.src}
#'
#' \url{https://github.com/numpy/numpy/pull/3685}
#'
pairwiseSum <- function(numbers) {
    .Call(`_psPairwiseSum`, as.double(numbers))
}

#' Using PreciceSums's default method, take a sum
#'
#' @inheritParams kahanSum
#' @return Sum of numbers
#' @export
psSum <- function(numbers) {
    .Call(`_psSum`, as.double(numbers))
}

##' Choose the type of sums to use for PreciceSums.
##'
##' Choose the types of sums to use in PreciceSums.  These are used in the
##' PreciceSums \code{sum} blocks and the \code{psSum} function
##'
##' @param type Sum type to use for \code{psSum} and \code{sum()} in
##'     PreciceSums code blocks.
##'
##' \code{pairwise} uses the pairwise sum (fast, default)
##'
##' \code{fsum} uses Python's fsum function (most accurate)
##'
##' \code{kahan} uses kahan correction
##'
##' \code{neumaier} uses Neumaier correction
##'
##' \code{klein} uses Klien correction
##'
##' \code{c} uses no correction, bud default/native summing
##'
##' @return nothing
##' @author Matthew L. Fidler
##' @export
##' @useDynLib PreciseSums, .registration=TRUE
psSetSum <- function(type=c("pairwise", "fsum", "kahan", "neumaier", "klein", "c")){
    i <- which(type == c("pairwise", "fsum", "kahan", "neumaier", "c", "klein"))
    invisible(.Call(`_psSetSum`, as.integer(i)))
}

##' Choose the type of product to use in PreciceSums.  These are used in the
##' PreciceSums \code{prod} blocks
##'
##' @param type  Product to use for \code{prod()} in PreciceSums blocks
##'
##' \code{long double} converts to long double, performs the
##' multiplication and then converts back.
##'
##' \code{double} uses the standard double scale for multiplication.
##'
##' @return nothing
##' @author Matthew L. Fidler
##' @export
psSetProd <- function(type=c("long double", "double", "logify")){
    i <- which(type == c("long double", "double", "logify"));
    invisible(.Call(`_psSetProd`, as.integer(i)))
}


#' Using PreciceSums's default method, take a product
#'
#' @inheritParams kahanSum
#' @return Product of numbers
#' @export
psProd <- function(numbers) {
    .Call(`_psProd`, as.double(numbers))
}
