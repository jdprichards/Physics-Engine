//=========================================================================================================
// Vector3.h: Encapsulates (x, y) Coordinates and Supporting Functions
// - Uses Template Functions to work on Integer, Float and Double Values
// Integer (Vector3i), Float(Vector3, Vector3f), Double(Vector3d)
//=========================================================================================================
// Template Classes usually put all code in Header.h files. However explicit template instantiation is
// used at the end of the .cpp file. Allows for code to be in the cpp file and
// the Class Interface here
//=========================================================================================================


#ifndef _VECTOR3_H_DEFINED_
#define _VECTOR3_H_DEFINED_

#include "MathsHelpers.h"

// Template Class to Support Float, Double or Int Coordinates
template<typename T> class Vector3T;


// Define convenient names for Vectors of different types to avoid Angle Bracket Syntax
using Vector3i = Vector3T<int>;		// 2D Vector with Int Coordinates
using Vector3f = Vector3T<float>;	// 2D Vector with Float Coordinates
using Vector3d = Vector3T<double>;	// 2D Vector with Double Coordinates
using Vector3 = Vector3f;			// Single name for 2D Vector with Float Coordinates (To use the Float version as Default)

// Full Decleration
template<typename T> class Vector3T
{
public:
	// Allow Public Access - For Simple, Well Defined Class

	// Vector Components
	T x;
	T y;
	T z;

	//================
	// Constructors
	//================

	// Default Constructor
#pragma warning (supress: 26495) // Disable Warning about Constuctor leaving values uninitalised
	Vector3T() {}

	// Construct with 2 Values
	Vector3T(const T xIn, const T yIn, const T zIn) : x(xIn), y(yIn), z(zIn) {}

	// Construct with Point to 2 Values
	explicit Vector3T(const T* elts)
	// Explicit doesn't allow Conversion from Pointer to Vector3 without writing the constuctor name
		// NOT ALLOWED:
		// Vector3 v = pointer;

		// ALLOWED:
		// Vector3 v = Vector3(pointer)
		: x(elts[0]), y(elts[1]), z(elts[2]) {}


	//=====================
	// Member Operators
	//=====================

	// Addition of Another Vector to this one (e.g. Position += Velocity)
	Vector3T& operator+=(const Vector3T& v);

	// Subtraction of Another Vector to this one (e.g. Velocity -= Acceleration)
	Vector3T& operator-=(const Vector3T& v);

	// Negate this Vector (e.g. Velocity = -Velocity)
	Vector3T& operator-();

	// Plus sign infront of Vector - Unary Positive and Usually does Nothing. Included for Completeness to reduce error when using Plus Signs (e.g. Velocity = +Velocity)
	Vector3T& operator+();

	// Multiply Vector by Scalar (Scales Vector)
	// Integer Vectors can be Multiplied by a Float but Resulting Vector will be Rounded to Integers
	Vector3T<T>& operator*=(FloatTypeFor<T> s);

	// Divide Vector by Scalar (Scales Vector)
	// Integer Vector can be Divided by a Float but the Resulting Vector will be Rounded to Integers
	Vector3T<T>& operator/=(FloatTypeFor<T> s);

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
template<typename T> Vector3T<T> operator+(const Vector3T<T>& v, const Vector3T<T>& w);

// Vector - Vector Subtraction
template<typename T> Vector3T<T> operator-(const Vector3T<T>& v, const Vector3T<T>& w);

// Vector - Scalar Multiplication / Division
template <typename T> Vector3T<T> operator* (const Vector3T<T>& v, FloatTypeFor<T> s);
template <typename T> Vector3T<T> operator* (FloatTypeFor<T> s, const Vector3T<T>& v);
template <typename T> Vector3T<T> operator/ (const Vector3T<T>& v, FloatTypeFor<T> s);

//========================
// Non-Member Functions
//========================

// Distance between two Vector3 Points
template<typename T> FloatTypeFor<T> Distance(const Vector3T<T>& v, const Vector3T<T>& w)
{
	return (w - v).Length();
}

// Dot Product of two given Vectors (Order Not Important) - Non-Member Function
template<typename T> T Dot(const Vector3T<T>& v, const Vector3T<T>& w);

// Cross Product of two given Vectors (Order Is Important) - Non-Member Function
template<typename T> Vector3T<T> Cross(const Vector3T<T>& v, const Vector3T<T>& w);

// Return Unit Length Vector in the SAME DIRECTION as the one given (NOT SUPPORTED FOR INT VECTORS: Vector3i)
template<typename T> Vector3T<T> Normalise(const Vector3T<T>& v);

// Returns Angle Between two Vectors (Return Type always a Float, when with Integer Version)
template<typename T> FloatTypeFor<T> AngleBetween(const Vector3T<T>& v, const Vector3T<T>& w);

#endif // !_Vector3_H_DEFINED_s
