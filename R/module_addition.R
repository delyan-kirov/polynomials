#' Title
#'
#' @param f polynomial
#' @param g polynomial
#'
#' @return the sum of the polynomials f and g
#' @export
#'
#' @examples polynomial_addition(c(1, 1, 1), c(-1/2, -1))
#'
#'
module_addition = function(f, g) #adds vectors in the module
{
  if(is.vector(f) == TRUE)
  {
    f = module_convert(f)
  }

  if(is.vector(g) == TRUE)
  {
    g = module_convert(g)
  }

  if (length(f) < length(g))
  {
    keeper = g
    g = f
    f = keeper
  }

  f1 = f[,1]
  f2 = f[,2]
  g1 = g[,1]
  g2 = g[,2]

  f1 = polynomial_simplify(f1)
  f2 = polynomial_simplify(f2)
  f1 = polynomial_addition(f1, g1)
  f2 = polynomial_addition(f2, g2)

  return(module_create(f1, f2))
}
