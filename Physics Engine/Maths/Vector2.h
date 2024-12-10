//=========================================================================================================
// Vector2.h: Encapsulates (x, y) Coordinates and Supporting Functions
// - Uses Template Functions to work on Integer, Float and Double Values
// Integer (Vector2i), Float(Vector2, Vector2f), Double(Vector2d)
//=========================================================================================================
// Template Classes usually put all code in Header.h files. However explicit template instantiation is
// used at the end of the .cpp file. Allows for code to be in the cpp file and
// the Class Interface here
//=========================================================================================================


#ifndef _VECTOR2_H_DEFINED_
#define _VECTOR2_H_DEFINED_

#include "MathsHelpers.h"

// Template Class to Support Float, Double or Int Coordinates
template<typename T> class Vector2T;


// Define convenient names for Vectors of different types to avoid Angle Bracket Syntax
using Vector2i = Vector2T<int>;		// 2D Vector with Int Coordinates
using Vector2f = Vector2T<float>;	// 2D Vector with Float Coordinates
using Vector2d = Vector2T<double>;	// 2D Vector with Double Coordinates
using Vector2 = Vector2f;			// Single name for 2D Vector with Float Coordinates (To use the Float version as Default)

// Full Decleration
template<typename T> class Vector2T
{
public:
	// Allow Public Access - For Simple, Well Defined Class

	// Vector Components
	T x;
	T y;

	//================
	// Constructors
	//================

	// Default Constructor
#pragma warning (supress: 26495) // Disable Warning about Constuctor leaving values uninitalised
	Vector2T() {}

	// Construct with 2 Values
	Vector2T(const T xIn, const T yIn) : x(xIn), y(yIn) {}

	// Construct with Pointer to 2 Values
	explicit Vector2T(const T* elts) : x(elts[0]), y(elts[1]) {}
	// Explicit doesn't allow Conversion from Pointer to Vector2 without writing the constuctor name
		// NOT ALLOWED:
		// Vector2 v = pointer;

		// ALLOWED:
		// Vector2 v = Vector2(pointer)
	

	//=====================
	// Member Operators
	//=====================

	// Addition of Another Vector to this one (e.g. Position += Velocity)
	Vector2T& operator+=(const Vector2T& v);

	// Subtraction of Another Vector to this one (e.g. Velocity -= Acceleration)
	Vector2T& operator-=(const Vector2T& v);

	// Negate this Vector (e.g. Velocity = -Velocity)
	Vector2T& operator-();

	// Plus sign infront of Vector - Unary Positive and Usually does Nothing. Included for Completeness to reduce error when using Plus Signs (e.g. Velocity = +Velocity)
	Vector2T& operator+();

	// Multiply Vector by Scalar (Scales Vector)
	// Integer Vectors can be Multiplied by a Float but Resulting Vector will be Rounded to Integers
	Vector2T<T>& operator*=(FloatTypeFor<T> s);

	// Divide Vector by Scalar (Scales Vector)
	// Integer Vector can be Divided by a Float but the Resulting Vector will be Rounded to Integers
	Vector2T<T>& operator/=(FloatTypeFor<T> s);

	//==========================
	// Other Member Functions
	//==========================

	// Returns the Length of the Vector (Return Type always a Float, when with a Integer Vector)
	FloatTypeFor<T> Length() const;

	// Returns the Square Length of the Vector (Return Type always a Float, when with a Integer Vector)
	FloatTypeFor<T> LengthSq() const;
};

//========================
// Non-Member Operators
//========================

// Vector - Vector Addition
template<typename T> Vector2T<T> operator+(const Vector2T<T>& v, const Vector2T<T>& w);

// Vector - Vector Subtraction
template<typename T> Vector2T<T> operator-(const Vector2T<T>& v, const Vector2T<T>& w);

// Vector - Scalar Multiplication / Division
template<typename T> Vector2T<T> operator* (const Vector2T<T>& v, FloatTypeFor<T> s);
template<typename T> Vector2T<T> operator* (FloatTypeFor<T> s, const Vector2T<T>& v);
template<typename T> Vector2T<T> operator/ (const Vector2T<T>& v, FloatTypeFor<T> s);

//========================
// Non-Member Functions
//========================

// Distance between two Vector2 Points
template<typename T> FloatTypeFor<T> Distance(const Vector2T<T>& v, const Vector2T<T>& w)
{
	return (w - v).Length();
}

// Dot Product of two given Vectors (Order Not Important)
template<typename T> T Dot(const Vector2T<T>& v, const Vector2T<T>& w);

// Return unit Length Vector in the SAME DIRECTION as the one given (NOT SUPPORTED FOR INT COORDINATES: Vector2i)
template<typename T> Vector2T<T> Normalise(const Vector2T<T>& v);

#endif // !_VECTOR2_H_DEFINED_s
