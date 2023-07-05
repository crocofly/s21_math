#include "s21_math.h"

#include <stdio.h>

int s21_abs(int x) {
  int res;
  if (x >= 0) {
    res = x;
  } else {
    res = -x;
  }
  return res;
}

long double s21_fabs(double x) {
  long double a = x;
  if (a < 0) {
    a = -a;
  }
  return a;
}

long double s21_ceil(double x) {
  long double res = x;
  if (x - (long int)x > 0) {
    res = (long int)x + 1;
  } else if (x - (long int)x < 0) {
    res = (long int)x;
  }
  return res;
}

long double s21_floor(double x) {
  long double res = (long int)x;
  if (x >= 0) {
    res = (long int)x;
  } else if (s21_fabs(x - (long int)x) > 0) {
    res = (long int)x - 1;
  }
  return res;
}

long double s21_fmod(double x, double y) {
  long double res;
  if (y == 0) {
    res = S21_NAN;
  } else {
    long double x1 = x;
    long double y1 = y;
    res = x1 - (int)(x1 / y1) * y1;
  }
  return res;
}

long double s21_sin(double x) {
  long double x1 = s21_fmod(x, 2 * S21_PI);
  long double res = 0;
  long double part = x1;
  unsigned long long n = 3;

  while (s21_fabs(part) > S21_EPS) {
    res += part;
    part *= (-1) * (x1 * x1) / (n * (n - 1));
    n += 2;
  }
  return res;
}

long double s21_cos(double x) {
  long double x1 = s21_fmod(x, 2 * S21_PI);
  long double res = 0;
  long double part = 1;
  unsigned long long n = 2;

  while (s21_fabs(part) > S21_EPS) {
    res += part;
    part *= (-1) * (x1 * x1) / (n * (n - 1));
    n += 2;
  }
  return res;
}

long double s21_tan(double x) {  //----- 2788400
  return s21_sin(x) / s21_cos(x);
}

long double s21_exp(double x) {  //-----
  long double x1 = x;
  long double res = 1;
  unsigned long long n = 1;
  int flag = x < 0;
  if (flag) x1 *= -1;
  long double part = x1;

  if (x > EXP_STEPEN_DOUBLE_MAX) {
    res = S21_INF;
  } else if (S21_IS_NAN(x)) {
    res = S21_NAN;
  } else if (x < EXP_STEPEN_DOUBLE_MIN) {
    res = 0.0;
  } else {
    while ((s21_fabs(part) > S21_EPS)) {
      res += part;
      part = part * x1 / ++n;
      if (x1 > 707 && n > 650) break;
    }
    res = flag ? (1 / res) : res;
  }
  return res;
}

long double s21_log(double x) {
  long double res = 0;
  unsigned long long n = 2;
  if (x == 0.0) {
    res = -S21_INF;
  } else if (x < 0.0) {
    res = S21_NAN;
  } else if (x == S21_INF) {
    res = x;
  } else {
    long double exp = 0;
    while (x >= 2.0) {
      exp++;
      x /= S21_E;
    }
    long double x1 = x;
    long double part = x1 - 1;
    while (s21_fabs(part) > S21_EPS) {
      res += part;
      part *= -((n - 1) * (x1 - 1)) / n;
      ++n;
    }
    res += exp;
  }
  return res;
}

long double s21_asin(double x) {
  long double res = 0;
  long double part = x;
  unsigned long long n = 3;
  if (x > -1. && x < 1.) {
    while (s21_fabs(part) > S21_EPS) {
      res += part;
      part *= (x * x) * (n - 2) * (n - 2);
      part /= (n * (n - 1));
      n += 2;
    }
  } else if (x == -1.) {  // 3 условия на доопределение области
    res = -S21_PI / 2;
  } else if (x == 1.) {
    res = S21_PI / 2;
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_acos(double x) {
  long double res;
  if ((x <= 1. && x > 0.) || (x >= -1. && x < 0.)) {
    res = S21_PI_2 - s21_asin(x);
  } else if (x == 0.) {  // 3 условия на доопределение области
    res = S21_PI_2;
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_sqrt(double x) {
  long double res = 1;
  if (x < 0.) {
    res = S21_NAN;
  } else if (x == 0.) {
    res = 0.;
  } else {
    long double prev = 123;
    while (s21_fabs(res - prev) > S21_EPS) {
      prev = res;
      res = (res + x / res) / 2;
    }
  }
  return res;
}

long double s21_atan(double x) { return s21_asin(x / s21_sqrt(1 + x * x)); }

long double s21_pow(double base, double exp) {
  long double res;
  if (exp == 0.) {
    res = 1.;
  } else if (base == 0. && exp >= 0.) {
    res = 0.;
  } else if (base == 0. && exp < 0) {
    res = S21_INF;
  } else if (base > 0. && exp != 0.) {
    res = s21_exp(exp * s21_log(base));
  } else if (exp == 1.) {
    res = base;
  } else if (base < 0. && exp != 0.) {
    if (s21_fmod(exp, 2.) == 0.)
      res = s21_exp(exp * s21_log(s21_fabs(base)));
    else if (s21_fabs(s21_fmod(exp, 2.)) == 1.)
      res = -s21_exp(exp * s21_log(s21_fabs(base)));
    else
      res = S21_NAN;
  }
  return res;
}
