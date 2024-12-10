//=========================================================================================================
// Matrix4x4.h: Encapsulates components of a 4x4 Affine Matirx and Supporting Functions
// - Uses Template Functions to work on Float and Double Values
// Float(Vector3, Vector3i), Double(Vector3d) - NOT SUPPORTING INT
//=========================================================================================================
// Template Classes usually put all code in Header.h files. However explicit template instantiation is
// used at the end of the .cpp file. Allows for code to be in the cpp file and
// the Class Interface here
//=========================================================================================================

#ifndef _MATRIX4X4_H_DEFINED_
#define _MATRIX4X4_H_DEFINED_

#include "Vector3.h"
#include "Vector4.h"

// Template Class to Support Float or Double Values. DO NOT use this typename, use simpler ones below.
template<typename T> class Matrix4x4T;

// Define Convinient names for Matrices of Different Types to avoid using Angle Bracket Syntax in Main Code
using Matrix4x4f = Matrix4x4T<float>;	// 4x4 Matrix with Float Values
using Matrix4x4d = Matrix4x4T<double>;	// 4x4 Matrix with Double Values
using Matrix4x4 = Matrix4x4f;		// Add Extra simple name for Float Values (Most Common Use-Case)

template<typename T> class Matrix4x4T
{
// ALLOW PUBLIC ACCESS. For simple, well-defined Class
public:
	// Matrix Elements
	T e00, e01, e02, e03;
	T e10, e11, e12, e13;
	T e20, e21, e22, e23;
	T e30, e31, e32, e33;

	//===============
	// Constructors
	//===============

	// Default Constructor - Leaves Values Uninitialised (For Performance)
#pragma warning(suppress : 26495)
	Matrix4x4T<T>() {}

	// Construct with 16 Values
	Matrix4x4T<T>
		(
			T v00, T v01, T v02, T v03,
			T v10, T v11, T v12, T v13,
			T v20, T v21, T v22, T v23,
			T v30, T v31, T v32, T v33
		) :
		e00(v00), e01(v01), e02(v02), e03(v03),
		e10(v10), e11(v11), e12(v12), e13(v13),
		e20(v20), e21(v21), e22(v22), e23(v23),
		e30(v30), e31(v31), e32(v32), e33(v33) {}

	// Construct using Pointer to 16 Values
	explicit Matrix4x4T<T>(T* elts)
		// Explicit doesn't allow Conversion from Pointer to Vector2 without writing the constuctor name
		// NOT ALLOWED:
		// Vector2 v = pointer;

		// ALLOWED:
		// Vector2 v = Vector2(pointer)
	{
		*this = *reinterpret_cast<Matrix4x4T<T>*>(elts);
	}

	// Construct Matrix from Position, Euler Angles(x, y and z Rotations), and Scale (x, y and z Seprately)
	Matrix4x4T<T>(Vector3T<T> position, Vector3T<T> rotations, Vector3T<T> scales)
	{
		//*this = MatrixScale(scales) * MatrixRotation(rotations) * MatrixTranslation(position);
	}

	// Construct Matrix from Position, Euler Angles (x, y and z rotation) and uniform scale
	// Scale and Rotations have Defaults, only Position is Required
	explicit Matrix4x4T<T>(Vector3T<T> position, Vector3T<T> rotations = { 0,0,0 }, float scale = 1)
		: Matrix4x4T<T>(position, rotations, { scale, scale, scale }) {} // Forward to Constructor Above

	//===============
	// Data Access
	//===============

	// Direct Access to the XYZ values in rows (0-3) of the Matrix using a Vector3
	// Returns a Reference so Result can be used to Get/Set Values e.g:
	//		float value = myMatrix.Row(3).y;
	//		myMatrix.Row(1) = Vector3(0, 1, 0);
	Vector3T<T>& Row(int row)
	{
		// Non-standard conversion but works in practice and is very useful in this particular circumstance
		// As with the constructor conversion above the "correct" ways to do this needs much more advacned C++
		return *reinterpret_cast<Vector3T<T>*>(&e00 + row * 4);
	}

	// Direct Access to XYZ values in rows (0-3) of the Matrix using a const Vector3
	// Using as a Getter when the Matrix is a Constant
	const Vector3T<T>& Row(int row) const
	{
		return Vector3T<T>(&e00 + row * 4);
	}

	// Direct Access to X axis of the Matrix
	// Returns a reference can be used to Get/Set
	//		Vector3 v = myMatrix.XAxis()
	//		myMatrix.XAxis() = {1, 2, 3}
	Vector3T<T>& XAxis{ return Row(0); }

	// Direct Access to Y axis of the Matrix
	// Returns a reference can be used to Get/Set
	//		Vector3 v = myMatrix.YAxis()
	//		myMatrix.YAxis() = {1, 2, 3}
	Vector3T<T>& YAxis{ return Row(1); }

	// Direct Access to Z axis of the Matrix
	// Returns a reference can be used to Get/Set
	//		Vector3 v = myMatrix.ZAxis()
	//		myMatrix.ZAxis() = {1, 2, 3}
	Vector3T<T>& ZAxis{ return Row(0); }

	// Direct Access to Position of the Matrix
	// Returns a reference can be used to Get/Set
	//		Vector3 v = myMatrix.Position()
	//		myMatrix.Position() = {1, 2, 3}
	Vector3T<T>& Position{ return Row(3); }


};

#endif // !_MATRIX4X4_H_DEFINED_
