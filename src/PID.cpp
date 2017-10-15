#include "PID.h"
#include <float.h>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;

  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  prev_cte = 0.0;
  has_prev_cte = false;

#if 0
  n = 100;

  i = 0;
  err = 0.0;
  mod = 0;

  dp[0] = Kp * 0.1;
  dp[1] = Ki * 0.1;
  dp[2] = Kd * 0.1;

  best_err = DBL_MAX;
#endif
}

void PID::UpdateError(double cte) {
  if(!has_prev_cte) {
    prev_cte = cte;
    has_prev_cte = true;
  }
  p_error = cte;
  i_error += cte;
  d_error = cte - prev_cte;
  prev_cte = cte;

#if 0
  i++;
  if(i <= n) {
    err += cte * cte;
    cout << "i:" << i << endl;
  } else if(i == (2*n)) {
    cout << "mod:" << mod << endl;
    err /= n;
    if(mod < 3) {
      if((mod%3) == 0) {
        Kp += dp[mod%3];
      } else if((mod%3) == 1) {
        Ki += dp[(mod%3)];
      } else if((mod%3) == 2) {
        Kd += dp[(mod%3)];
      }
      mod += 3;
    } else if(mod < 6) {
      if(err < best_err) {
        best_err = err;
        dp[(mod%3)] *= 1.1;
        mod = (mod + 1) % 3;
      } else {
        if((mod%3) == 0) {
          Kp -= 2 * dp[0];
        } else if((mod%3) == 1) {
          Ki -= 2 * dp[1];
        } else {
          Kd -= 2 * dp[2];
        }
        mod += 3;
      }
    } else {
      if(err < best_err) {
        best_err = err;
        dp[(mod%3)] *= 1.1;
      } else {
        if((mod%3) == 0) {
          Kp += dp[0];
        } else if((mod%3) == 1) {
          Ki += dp[1];
        } else {
          Kd += dp[2];
        }
        dp[(mod%3)] *= 0.9;
      }
      mod = (mod + 1) % 3;
    }
    i = 0;
  }
#endif
}

double PID::TotalError() {
    return -Kp * p_error - Kd * d_error - Ki * i_error;
}

