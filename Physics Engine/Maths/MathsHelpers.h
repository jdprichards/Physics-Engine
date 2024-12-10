//=========================================================================
// MathsHelpers.h: Contains Conveient Maths Functions
// - Uses Template Functions to work on Integer, Float and Double Values
//=========================================================================

#ifndef _MATHS_HELPERS_H_DEFINED_
#define _MATHS_HELPERS_H_DEFINED_

#include <cmath>
#include <numbers>
#include <type_traits>

// Special type to handle situations where Floating Point numbers are exceptionally required Integer-based template classes
// For Example: Vector2i (2D Vector with Int coords) needs a length function that returns a Float not an Int
// Instances:
// FloatTypeFor<int> is float
// FloatTypeFor<float> is float
// FloatTypeFor<double> is double
template<typename T> using FloatTypeFor = std::conditional_t<std::is_floating_point_v<T>, T, float>;

// Test is Floating Point value is Approximately 0
template <typename T> bool IsZero(const T x);

// 1 / Sqrt. Used often (e.g. Normalising) so can be optimised, so it gets it's own function
// Supports Int, Float and Double Values.
// Use of conditional_t ensures Int version returns a Float result
template<typename T, typename U = std::conditional_t<std::is_integral_v<T>, float, T>> constexpr U InvSqrt(const T x)
{
	return 1 / std::sqrt(x);
}

template<typename T, typename U = std::conditional_t<std::is_integral_v<T>, float, T>> constexpr U Square(const T x)
{
	return x * x;
}

// Pass an angle in Degrees, Returns angle in Radians
// Supports Int, Float and Double values. use of conditional_t ensure Int versions Returns a Float result
template<typename T, typename U = std::conditional_t<std::is_integral_v<T>, float, T>> constexpr U ToRadians(T d)
{
	return static_cast<U>(d) * std::numbers::pi_v<U> / 180;
}

// Pass an angle in Radians. Returns angle in Degrees
// Supports int, Float and Dobule values. Use of conditional_t ensures Int versions Returns a Float result
template<typename T, typename U = std::conditional_t<std::is_integral_v<T>, float, T>> constexpr U ToDegrees(T r)
{
	return static_cast<U>(r) * 180 / std::numbers::pi_v<U>;
}

// Return random number from a to b (inclusive> - Will return Int, Float or Double of a Random number matching Type of parameters a & b
template<typename T> T Random(const T a, const T b);

#endif // !_MATHS_HELPERS_H_DEFINED_


