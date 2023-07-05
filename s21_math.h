#ifndef SRC_S21_MATH
#define SRC_S21_MATH
#include <stdio.h>

#define S21_EPS 1e-25
#define S21_PI 3.141592653589793115997963468544185161590576171875
#define S21_PI_2 1.5707963267948965579989817342720925807952880859375
#define S21_E 2.71828182845904523536028747135266250
#define S21_NAN 0.0 / 0.0
#define S21_IS_NAN __builtin_isnan
#define S21_INF __builtin_inf()  // or 1.0 / 0.0
#define EXP_STEPEN_DOUBLE_MAX 709.7827
#define EXP_STEPEN_DOUBLE_MIN -708.3964

int s21_abs(int x);

long double s21_fabs(double x);

long double s21_ceil(double x);

long double s21_floor(double x);

long double s21_fmod(double x, double y);

long double s21_sin(double x);

long double s21_cos(double x);

long double s21_tan(double x);

long double s21_exp(double x);

long double s21_log(double x);

long double s21_asin(double x);

long double s21_acos(double x);

long double s21_sqrt(double x);

long double s21_atan(double x);

long double s21_pow(double base, double exp);

#endif  // SRC_S21_MATH.H