#' Title
#'
#'gives you the result after performing the division algorithm
#'does not give remainder
#'
#' @param f polynomial
#' @param g polynomial
#'
#' @return polynomial
#' @export
#'
#' @examples
polynomial_division = function(f, g)
{
  remainder = -1
  quotient = seq()
  summa = seq()
  h = seq()

  if (polynomial_degree(f) < polynomial_degree(h))
  {
    keeper = g
    g = f
    f = keeper
  }

  if (polynomial_degree(g) == -Inf)
  {
    return(NA)
  }

  for (i in 1:length(f))
  {
    difference = polynomial_degree(f) - polynomial_degree(g)

    for (j in 1:(difference+1))
    {
      if (j == 1)
      {
        h[j] = (1/g[1]*f[1])
      }
      else
      {
        h[j] = 0
      }
    }

    if (i == 1)
    {
      quotient = h
    }
    else
    {
      quotient = polynomial_addition(quotient, h)
    }

    h = polynomial_product(g, h)
    f = polynomial_addition(f, -1*h)
    h = seq()
    f = polynomial_simplify(f)

    if (polynomial_degree(f) < polynomial_degree(g))
    {
      break
    }
  }
  return(quotient)
}
