#' Title
#'
#'removes the zero coefficients at the start
#'
#' @param f polynomial
#'
#' @return polynomial
#' @export
#'
#' @examples polynomial_simplify(c(0,1,1,1)) gives c(1, 1, 1)
#'
polynomial_simplify = function(f)
{
  h = seq()
  zeros = 0
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
    return(0)
  }

  for (i in 1:(length(f) - zeros))
  {
    h[i] = f[i+zeros]
  }
  return(h)
}

