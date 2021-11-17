#' Title
#'
#' @param f polynomial
#' @param g polynomial
#'
#' @return polynomial sum
#' @export
#'
#' @examples
polynomial_addition = function(f, g)
{

  if (polynomial_degree(f) == -Inf | polynomial_degree(g) == -Inf)
  {
    if (polynomial_degree(g) == -Inf)
    {
      return(f)
    }
    else
    {
      return(g)
    }
  }

  if (polynomial_degree(f) < polynomial_degree(g))
  {
    keeper = g
    g = f
    f = keeper
  }

  degree = max(polynomial_degree(f), polynomial_degree(g))
  h = seq()
  summa = seq()
  difference = length(f) - length(g)

  for (i in 1:(degree+1))
  {
    if (i <= difference)
    {
      h[i] = 0
    }
    else
    {
      h[i] = g[i - difference]
    }
  }

  for (i in 1:(degree+1))
  {
    summa[i] = f[i] + h[i]
  }
  return(summa)
}
