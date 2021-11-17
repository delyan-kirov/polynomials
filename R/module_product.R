#' Title
#'
#'defines a product function: Q[x]^2 x Q[x]^2 -> Q[x]
#'
#' @param f vector
#' @param g vector
#'
#' @return vector
#' @export
#'
#' @examples
module_product = function(f, g) #adds vectors in the module
{
  if (length(f) < length(g))
  {
    keeper = g
    g = f
    f = keeper
  }

  if(is.vector(f) == TRUE)
  {
    f = module_convert(f)
  }

  if(is.vector(g) == TRUE)
  {
    g = module_convert(g)
  }


  f1 = f[,1]
  f2 = f[,2]
  g1 = g[,1]
  g2 = g[,2]

  f1 = polynomial_product(f1, g1)
  f2 = polynomial_product(f2, g2)

  return(module_create(f1, f2))
}
