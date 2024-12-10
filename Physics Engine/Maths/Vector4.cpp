//=========================================================================================================
// Vector3.h: Encapsulates (x, y) Coordinates and Supporting Functions
// - Uses Template Functions to work on Float and Double Values
// Float(Vector3, Vector3i), Double(Vector3d) - NOT SUPPORTING INT
//=========================================================================================================
// Explicit Non-Member Function Definitions found at end of .cpp file
//=========================================================================================================

#include "Vector4.h"

//=============================================================================================
// Template Instantiation
//=============================================================================================
// Instantiate this Template Class for specific Numeric Types. Prevents use of other Types
// and allows for Code to be placed in .cpp file
//=============================================================================================

template class Vector4T<float>;		// Vector4 / Vector4f
template class Vector4T<double>;	// Vector4d
// NOT SUPPORTING int Vector4