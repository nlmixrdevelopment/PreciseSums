% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/sums.R
\name{kahanSum}
\alias{kahanSum}
\title{Using the Kahan method, take a more accurate sum}
\usage{
kahanSum(numbers)
}
\arguments{
\item{numbers}{A vector of numbers to sum.}
}
\value{
Sum of numbers
}
\description{
Using the Kahan method, take a more accurate sum
}
\examples{
sum(c(1,1e100,1,-1e100)) ## Should be 2, gives 0
kahanSum(c(1,1e100,1,-1e100)) ## Not accurate enough for the correct result. (still = 0)
}
\references{
\url{https://en.wikipedia.org/wiki/Kahan_summation_algorithm}
}
