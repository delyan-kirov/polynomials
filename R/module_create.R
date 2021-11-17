#' Title
#'
#'creates a 2-dimensional vector with coordinates the polynomials f and g
#'
#'
#' @param f polynomial
#' @param g polynomial
#'
#' @return vector
#' @export
#'
#' @examples
module_create = function(f, g) #makes a the module matrix out of 2 vectors
{
  if (polynomial_degree(f) >= polynomial_degree(g))
  {
    g = polynomial_addition(polynomial_addition(f, g), -1*f)
    output = matrix(c(f, g), ncol = 2)
    return(output)
  }

  if (polynomial_degree(f) < polynomial_degree(g))
  {
    f = polynomial_addition(polynomial_addition(f, g), -1*g)
    output = matrix(c(f, g), ncol = 2)
    return(output)
  }
}
