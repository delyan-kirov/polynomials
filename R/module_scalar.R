#' Title
#'scales a vector with a in Q[x]
#'
#' @param f vector
#' @param a scalar
#'
#' @return vector
#' @export
#'
#' @examples
module_scalar = function(f, a)
{
  if(is.vector(f) == TRUE)
  {
    f = module_convert(f)
  }
  f1 = f[,1]
  f2 = f[,2]

  f1 = polynomial_simplify(f1)
  f2 = polynomial_simplify(f2)

  f1 = polynomial_product(f1, a)
  f2 = polynomial_product(f2, a)

  return(module_create(f1, f2))
}
