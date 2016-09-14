#include <Rcpp.h>
#include "htdp.h"
using namespace Rcpp;

// Reimplementation of interactive subroutine GETMDY in htdp.for
void c_getmdy(const int month, const int iday, const int iyear, double *date, int *mins)
{
  // Calculate modified Julian date
  int mjd = 0, mjd0 = 0, mjd1 = 0, i = 1;
  iymdmj_(&iyear, &month, &iday, &mjd);

  // Calculate time in decimal years (date)
  iymdmj_(&iyear, &i, &i, &mjd0);
  int iyear1 = iyear + 1;
  iymdmj_(&iyear1, &i, &i, &mjd1);
  int day = mjd - mjd0;
  int denom = mjd1 - mjd0;
  *date = iyear + (day / denom);

  // calculate Julian time in minutes (mins)
  *mins = mjd * 24 * 60;

  return;
}

// [[Rcpp::export]]
void htdpinit()
{
  // Obtain parameters defining crustal motion model
  model_();

  // Initialize transformation parameters from ITRF94 to other reference frames
  settp_();

  // Initialize conversion table between reference frame identifiers
  setrf_();

  return;
}

// [[Rcpp::export]]
DataFrame displacement(NumericMatrix xy, Date start, Date end, int iopt)
{
  if (iopt < 1 || iopt > 23 || iopt == 4) {
    stop("Invalid reference frame");
  }

  // Extract MDY for GETMDY subroutine
  int d0 = start.getDay();
  int m0 = start.getMonth();
  int y0 = start.getYear();
  int d1 = end.getDay();
  int m1 = end.getMonth();
  int y1 = end.getYear();

  if (y0 <= 1906 || y1 <= 1906) {
    stop("The model is not valid for dates prior to 1906");
  }

  // Calculate decimal years and Julian time in minutes
  int min0 = 0, min1 = 0;
  double date0 = 0, date1 = 0;
  c_getmdy(m0, d0, y0, &date0, &min0);
  c_getmdy(m1, d1, y1, &date1, &min1);

  //----------------------------------------------------------------------------
  // Main HTDP Routines
  //----------------------------------------------------------------------------

  int nrows = xy.nrow();

  double lat0 = 0, lon0 = 0, eht0 = 0;
  double lat1 = 0, lon1 = 0, eht1 = 0;
  int jregn = 0;
  double vn = 0, ve = 0, vu = 0;
  double dn = 0, de = 0, du = 0;

  // Output vectors
  std::vector<double> dx;
  std::vector<double> dy;
  std::vector<double> dz;

  for (int i = 0; i < nrows; i++) {
    // X/Y in positive N/W, radians
    lat0 = xy(i,1) * (M_PI / 180.0);
    lon0 = -xy(i,0) * (M_PI / 180.0);

    // Predict velocity in iopt reference frame
    predv_(&lat0, &lon0, &eht0, &date0, &iopt, &jregn, &vn, &ve, &vu);

    // Predict coordinates and displacements from time MIN1 to time MIN2
    newcor_(&lat0, &lon0, &eht0, &min0, &min1, &lat1, &lon1, &eht1, &dn, &de, &du, &vn, &ve, &vu);

    dx.push_back(de);
    dy.push_back(dn);
    dz.push_back(du);
  }

  Rcpp::DataFrame df = Rcpp::DataFrame::create(Rcpp::Named("dx")=dx, Rcpp::Named("dy")=dy, Rcpp::Named("dz")=dz);

  return df;
}
