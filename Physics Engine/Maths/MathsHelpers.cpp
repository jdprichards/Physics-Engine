//=========================================================================
// MathsHelpers.cpp: Contains Conveient Maths Functions
// - Uses Template Functions to work on Integer, Float and Double Values
//=========================================================================

#include "MathsHelpers.h"

//=================================================
// Float and Double Versions of IsZero Function
//=================================================

// Test if Float value is Approximately Equal to 0
// Epsilon value is the Range around Zero which is considered Zero
const float EPSILON32 = 0.5e-6f;
template<> bool IsZero<float>(const float x)
{
	return std::abs(x) < EPSILON32;
}

// Test if Double value is Approximately Equal to 0
// Epsilon value is the Range around Zero which is considered Zero
const double EPSILON64 = 0.5e-15;
template<> bool IsZero<double>(const double x)
{
	return std::abs(x) < EPSILON64;
}

//==================
// Random Numbers
//==================

// Retuerns a Random Integer from a to b (inclusive)
// Can only return up to RAND_MAX different values, spread evenly across the given range
// RAND_MAX is defined in stdlib.h and is compiler specific (32767 in vs)
template<> int Random<int>(const int a, const int b)
{
	// Could just use a + rand() % (b-a), but using a more complex form to allow the range
	// to exceed RAND_MAX and still return values spread across range
	
	int t = (b - a + 1) * rand();
	return t == 0 ? a : a + (t - 1) / RAND_MAX;
}

// Return a Random Float from a to b (inclusive)
// Can only return up to RAND_MAX different values, spread evenly across the given range
// RAND_MAX is defined in stdlib.h and is compiler specific (32767 in vs)
template<> float Random<float>(const float a, const float b)
{
	return a + (b - a) * (static_cast<float>(rand() / RAND_MAX));
}

// Return a Random Double from a to b (inclusive)
// Can only return up to RAND_MAX different values, spread evenly across the given range
// RAND_<AX is defined in stdlib.h and is compiler specific (32767 in vs)
template<> double Random<double>(const double a, const double b)
{
	return a + (b - a) * (static_cast<double>(rand() / RAND_MAX));
}
