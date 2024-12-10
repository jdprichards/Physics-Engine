//=========================================================================================================
// Vector3.h: Encapsulates (x, y, z, w) Coordinates and Supporting Functions
// - Uses Template Functions to work on Float and Double Values
// Float(Vector4, Vector4f), Double(Vector4d) - NOT SUPPORTING INT
//=========================================================================================================
// Template Classes usually put all code in Header.h files. However explicit template instantiation is
// used at the end of the .cpp file. Allows for code to be in the cpp file and
// the Class Interface here
//=========================================================================================================

#ifndef _VECTOR4_H_DEFINED_
#define _VECTOR4_H_DEFINED_

#include "Vector3.h"

// Template Class to Support Float or Double Coordinates. DO NOT use this type, use simpler types below.
template<typename T> class Vector4T;

// Define conveinient names for Vectors of diffrent types ot avoid messy angle bracket syntax
using Vector4f = Vector4T<float>;	// Vector4 with float coords
using Vector4d = Vector4T<double>;	// Vector4 with double coords
// NOT SUPPORTING int Vector4

// Full Declaration
template<typename T> class Vector4T
{
// ALLOW PUBLIC ACCESS. For such a simple, well-defined Class
public:
	T x;
	T y;
	T z;
	T w;

	//===============
	// Constructors
	//===============

	// Default Constructor - Leaves Values uninitialised (For Performance)
#pragma warning(supress: 26495)
	Vector4T<T>() {}

	// Construct with 4 Values
	Vector4T(const T xIn, const T yIn, const T zIn, const T wIn)
		: x(xIn), y(yIn), z(zIn), w(wIn) {}

	// Construct with Pointer to 4 Values
	explicit Vector4T(const T* elts)
		// Explicit doesn't allow Conversion from Pointer to Vector3 without writing the constuctor name
		// NOT ALLOWED:
		// Vector3 v = pointer;

		// ALLOWED:
		// Vector3 v = Vector3(pointer)
		: x(elts[0]), y(elts[1]), z(elts[2]), w(elts[3]) {}

	// Cast to Vector3 - Allows use of Vector3 Methods on x, y, z members only (e.g. Dot Product)
	operator Vector3T<T>()
	{
		return Vector3T<T>(&x);
	}

};

// NO Other Content for Vector4. Although the Usual Addition, Subtraction, Dot, Cross, Length, etc. Functions can
// be supported. The 4th Value (1 for Point, 0 for Vector) makes these functions perform
// non-intuitively. 
// IF these feature are needed CAST TO Vector3:
//		Vector3 vector3 = Vector3(vector4)

#endif // !_VECTOR4_H_DEFINED_
