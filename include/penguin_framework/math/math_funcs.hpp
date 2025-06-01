#pragma once

#include <penguin_framework/math/math_types.hpp>
#include <penguin_framework/math/math_compat.hpp>
#include <cmath>
#include <algorithm>
#include <cfloat>

namespace penguin::math {

    constexpr bool is_equal_approx(double a, double b, double p_epsilon = epsilon) {

        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        if (compat::p_isinf(a) || compat::p_isinf(b)) {
            return a == b;
        }

        return compat::p_abs(a - b) <= (std::max(compat::p_abs(a), compat::p_abs(b)) * p_epsilon);
    }

    constexpr bool is_equal_approx(float a, float b, float p_epsilon = static_cast<float>(epsilon)) {

        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        if (compat::p_isinf(a) || compat::p_isinf(b)) {
            return a == b;
        }

        return compat::p_abs(a - b) <= (std::max(compat::p_abs(a), compat::p_abs(b)) * p_epsilon);
    }
    
    constexpr bool is_almost_equal(double a, double b, double absolute_epsilon = DBL_EPSILON * 10, double relative_epsilon = epsilon) {
        if (a == b) {
            return true;
        }

        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        float diff = compat::p_abs(a - b);
        if (diff <= absolute_epsilon) {
            return true;
        }

        return diff <= (std::max(compat::p_abs(a), compat::p_abs(b)) * relative_epsilon);
    }

    constexpr bool is_almost_equal(float a, float b, float absolute_epsilon = FLT_EPSILON * 10, float relative_epsilon = static_cast<float>(epsilon)) {
        if (a == b) {
            return true;
        }

        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        float diff = compat::p_abs(a - b);
        if (diff <= absolute_epsilon) {
            return true;
        }

        return diff <= (std::max(compat::p_abs(a), compat::p_abs(b)) * relative_epsilon);
    }

    constexpr bool is_zero_approx(double a) {
        return compat::p_abs(a) < epsilon;
    }

    constexpr bool is_zero_approx(float a) {
        return compat::p_abs(a) < static_cast<float>(epsilon);
    }

    constexpr bool is_def_greater_than(double a, double b, double p_epsilon = epsilon) {
        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (compat::p_isinf(a) && a > 0 && compat::p_isinf(b) && b < 0) {
            return true;
        }

        if (compat::p_isinf(a) && a > 0 && !compat::p_isinf(b)) {
            return true;
        }

        if (!compat::p_isinf(a) && compat::p_isinf(b) && b < 0) {
            return true;
        }

        return (a - b) > ((compat::p_abs(a) < compat::p_abs(b) ? compat::p_abs(b) : compat::p_abs(a)) * epsilon);
    }

    constexpr bool is_def_greater_than(float a, float b, float p_epsilon = static_cast<float>(epsilon)) {
        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (compat::p_isinf(a) && a > 0 && compat::p_isinf(b) && b < 0) {
            return true;
        }

        if (compat::p_isinf(a) && a > 0 && !compat::p_isinf(b)) {
            return true;
        }

        if (!compat::p_isinf(a) && compat::p_isinf(b) && b < 0) {
            return true;
        }

        return (a - b) > ((compat::p_abs(a) < compat::p_abs(b) ? compat::p_abs(b) : compat::p_abs(a)) * epsilon);
    }

    constexpr bool is_def_less_than(double a, double b, double p_epsilon = epsilon) {
        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (compat::p_isinf(b) && b > 0 && compat::p_isinf(a) && a < 0) {
            return true;
        }

        if (compat::p_isinf(b) && b > 0 && !compat::p_isinf(a)) {
            return true;
        }

        if (!compat::p_isinf(b) && compat::p_isinf(a) && a < 0) {
            return true;
        }

        return (b - a) > ((compat::p_abs(a) < compat::p_abs(b) ? compat::p_abs(b) : compat::p_abs(a)) * epsilon);
    }

    constexpr bool is_def_less_than(float a, float b, float p_epsilon = static_cast<float>(epsilon)) {
        if (compat::p_isnan(a) || compat::p_isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (compat::p_isinf(b) && b > 0 && compat::p_isinf(a) && a < 0) {
            return true;
        }

        if (compat::p_isinf(b) && b > 0 && !compat::p_isinf(a)) {
            return true;
        }

        if (!compat::p_isinf(b) && compat::p_isinf(a) && a < 0) { 
            return true; 
        }

        return (b - a) > ((compat::p_abs(a) < compat::p_abs(b) ? compat::p_abs(b) : compat::p_abs(a)) * epsilon);
    }

}