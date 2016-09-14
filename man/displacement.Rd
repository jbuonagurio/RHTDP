\name{displacement}
\alias{displacement}
\title{Estimate horizontal displacements between two dates}
\description{
Returns an \R \code{data.frame} containing the crustal displacement in meters at a specified location from time t1 to time t2. The estimated displacement equals the velocity at this location multiplied by the time difference (t2 - t1) plus all coseismic and postseismic motion that has occurred between these two times.
}
\usage{
displacement(xy, start, end, iopt)
}
\arguments{
  \item{xy}{A matrix of longitude and latitude coordinates in decimal degrees}
  \item{start}{The starting date}
  \item{end}{The ending date}
  \item{iopt}{The key identifying the reference frame for the input values. See \code{\link{iopt}} for a list of supported values.}
}
\value{
  A \code{data.frame} with 3 columns:
    \item{dx}{Eastward displacement (meters)}
    \item{dy}{Northward displacement (meters)}
    \item{dz}{Upward displacement (meters)}
}
\examples{
beta <- matrix(data=c(-121.7722, 36.6698), nrow=1)
d0 <- as.Date("1989-10-16")
d1 <- as.Date("1989-10-18")
displacement(beta, d0, d1, 1)
}
\seealso{
  \code{\link{iopt}}
}
