#' Title
#'
#'performs the euclidean algorithm
#'
#' @param f polynomial
#' @param g polynomial
#'
#' @return Bezout coefficients and gcd(f,g)
#' @export
#'
#' @examples
#'
polynomial_EU = function(f, g)
{
  if (polynomial_degree(f) < polynomial_degree(g))
  {
    keeper = f
    f = g
    g = keeper
  }

  if (polynomial_degree(g) == -Inf | polynomial_degree(g) == 0)
  {
    print(f)
    return(c(1,0))
  }

  f_initial = f
  g_initial = g
  #vect1 = [1, 0] - (divisor)*[0,1]
  divisor = polynomial_division(f, g)
  vect1 = module_addition(c(1,0), -1*module_scalar(c(0,1), divisor))

  while(polynomial_degree(g) > 0)
  {
    remainder = polynomial_remainder(f, g)
    f = g
    g = remainder

    if (polynomial_degree(remainder) == -Inf)
    {
      print(g_initial)
      return(c(0,1))
    }

    divisor = polynomial_division(f, g)

    if (polynomial_degree(f) == polynomial_degree(g_initial))
    {
      #vect2 = [0, 1] - (divisor)*vect1
      vect2 = module_addition(c(0,1), -1*module_scalar(vect1, divisor))
    }

    if (polynomial_degree(f) < polynomial_degree(g_initial))
    {
      keeper = vect2
      summand = (-1*module_scalar(vect2, divisor))
      vect2 = module_addition( summand, vect1)
      vect1 = keeper
    }
  }
  print(g)
  return(vect1)
}
