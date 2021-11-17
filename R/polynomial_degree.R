#' Title
#'
#' @param f polynomial
#'
#' @return degree of polynomial, 0 has degree -inf
#' @export
#'
#' @examples polynomial_degree(c(1,1,1))
#'
#'
polynomial_degree = function(f)
{
  if (length(f) == 1 && f == 0)
  {
    return (-Inf)
  }

  else
  {
    zeros = 0
    count = 0
    for (i in 1:length(f))
    {
      if (f[i] == 0)
      {
        zeros = zeros + 1
      }
      if (f[i] != 0)
      {
        break
      }
    }
    if (zeros == length(f))
    {
      return(-Inf)
    }

    for (i in (zeros+1):length(f))
    {
      count = count + 1
    }
    return(count-1)
  }
}
