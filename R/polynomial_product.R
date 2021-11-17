#' Title
#'multiplies the polynomials f and g
#'
#' @param f polynomial
#' @param g polynomial
#'
#' @return polynomial
#' @export
#'
#' @examples
polynomial_product = function(f, g)
{
  if (polynomial_degree(f) == -Inf | polynomial_degree(g) == -Inf)
  {
    return(0)
  }

  if (polynomial_degree(f) == 0 | polynomial_degree(g) == 0)
  {
    return(f*g)
  }

  product = rep(0, length(f) + length(g) - 1)
  h = product

  for (i in 1:length(f))
  {
    for (j in 1:length(g))
    {
      if (f[i] == 0 | g[j] == 0)
      {
        break
      }

      h[i + j - 1] = f[i]*g[j]
      product = product + h
      h = rep(0, length(f) + length(g) - 1)
    }
  }

  return(product)
}
