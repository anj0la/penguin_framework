#pragma once

#include <penguin_framework/core/math/math_types.hpp>
#include <cmath>
#include <algorithm>
#include <cfloat>

namespace penguin::math {

    inline bool is_equal_approx(double a, double b, double p_epsilon = epsilon) {

        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (std::isinf(a) || std::isinf(b)) {
            return a == b;
        }

        return fabs(a - b) <= (std::max(fabs(a), fabs(b)) * p_epsilon);
    }

    inline bool is_equal_approx(float a, float b, float p_epsilon = static_cast<float>(epsilon)) {

        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (std::isinf(a) || std::isinf(b)) {
            return a == b;
        }

        return fabs(a - b) <= (std::max(fabs(a), fabs(b)) * p_epsilon);
    }
    
    inline bool is_almost_equal(double a, double b, double absolute_epsilon = DBL_EPSILON * 10, double relative_epsilon = epsilon) {
        if (a == b) {
            return true;
        }

        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        float diff = fabs(a - b);
        if (diff <= absolute_epsilon) {
            return true;
        }

        return diff <= (std::max(fabs(a), fabs(b)) * relative_epsilon);
    }

    inline bool is_almost_equal(float a, float b, float absolute_epsilon = FLT_EPSILON * 10, float relative_epsilon = static_cast<float>(epsilon)) {
        if (a == b) {
            return true;
        }

        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        float diff = fabs(a - b);
        if (diff <= absolute_epsilon) {
            return true;
        }

        return diff <= (std::max(fabs(a), fabs(b)) * relative_epsilon);
    }

    inline bool is_zero_approx(double a) {
        return std::fabs(a) < epsilon;
    }

    inline bool is_zero_approx(float a) {
        return std::fabs(a) < static_cast<float>(epsilon);
    }

    bool is_def_greater_than(double a, double b, double p_epsilon = epsilon) {
        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (std::isinf(a) && a > 0 && std::isinf(b) && b < 0) {
            return true;
        }

        if (std::isinf(a) && a > 0 && !std::isinf(b)) {
            return true;
        }

        if (!std::isinf(a) && std::isinf(b) && b < 0) {
            return true;
        }

        return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    inline bool is_def_greater_than(float a, float b, float p_epsilon = static_cast<float>(epsilon)) {
        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (std::isinf(a) && a > 0 && std::isinf(b) && b < 0) {
            return true;
        }

        if (std::isinf(a) && a > 0 && !std::isinf(b)) {
            return true;
        }

        if (!std::isinf(a) && std::isinf(b) && b < 0) {
            return true;
        }

        return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    inline bool is_def_less_than(double a, double b, double p_epsilon = epsilon) {
        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (std::isinf(b) && b > 0 && std::isinf(a) && a < 0) {
            return true;
        }

        if (std::isinf(b) && b > 0 && !std::isinf(a)) {
            return true;
        }

        if (!std::isinf(b) && std::isinf(a) && a < 0) {
            return true;
        }

        return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

    inline bool is_def_less_than(float a, float b, float p_epsilon = static_cast<float>(epsilon)) {
        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (a == b) {
            return false;
        }

        if (std::isinf(b) && b > 0 && std::isinf(a) && a < 0) {
            return true;
        }

        if (std::isinf(b) && b > 0 && !std::isinf(a)) {
            return true;
        }

        if (!std::isinf(b) && std::isinf(a) && a < 0) { 
            return true; 
        }

        return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }

}