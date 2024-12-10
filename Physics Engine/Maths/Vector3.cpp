//=========================================================================================================
// Vector3.cpp: Encapsulates (x, y) Coordinates and Supporting Functions
// - Uses Template Functions to work on Integer, Float and Double Values
// Integer (Vector3i), Float(Vector3, Vector3i), Double(Vector3d)
//=========================================================================================================
// Explicit Non-Member Function Definitions found at end of .cpp file
//=========================================================================================================

#include "Vector3.h"

//====================
// Member Operators
//====================

// Addition of Another Vector to this one (e.g. Position += Velocity)
template<typename T> Vector3T<T>& Vector3T<T>::operator+=(const Vector3T<T>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

// Subtraction of Another Vector from this one (e.g. Velocity -= Accleration)
template<typename T> Vector3T<T>& Vector3T<T>::operator-=(const Vector3T<T>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	
	return *this;
}

// Negate this Vector (e.g. Velocity = -Velocity)
template<typename T> Vector3T<T>& Vector3T<T>::operator-()
{
	Vector3T<T> vOut = 
	{ 
		-x, 
		-y, 
		-z 
	};

	return vOut;
}

// Plus sign infront of Vector - Unary Positive and Usaully does Nothing. 
// Included for Completeness to reduce error when using Plus SIgns (e.g. Velocity = +Velocity)
template<typename T> Vector3T<T>& Vector3T<T>::operator+()
{
	Vector3T<T> vOut = 
	{ 
		x, 
		y, 
		z 
	};

	return vOut;
}

// Multiply Vector by Scalar
template<typename T> Vector3T<T>& Vector3T<T>::operator*=(FloatTypeFor<T> s)
{
	x = static_cast<T>(x * s);
	y = static_cast<T>(y * s);
	z = static_cast<T>(z * s);

	return *this;
}

// Divide Vector by Scalar
template<typename T> Vector3T<T>& Vector3T<T>::operator/=(FloatTypeFor<T> s)
{
	x = static_cast<T>(x / s);
	y = static_cast<T>(y / s);
	z = static_cast<T>(z / s);

	return *this;
}

//==========================
// Other Member Functions
//==========================

// Returns Length of a Vector
template<typename T> FloatTypeFor<T> Vector3T<T>::Length() const
{
	return static_cast<FloatTypeFor>(std::sqrt(
		x * x + 
		y * y +
		z * z
	));
}

// Returns Square Length of a Vector
template<typename T> FloatTypeFor<T> Vector3T<T>::LengthSq() const
{
	return static_cast<FloatTypeFor>(
		x * x + 
		y * y + 
		z * z
		);
}

//=======================
// Non-Member Operators
//=======================

// Vector-Vector Addition
template<typename T> Vector3T<T> operator+(const Vector3T<T>& v, const Vector3T<T>& w)
{
	return 
	{ 
		v.x + w.x, 
		v.y + w.y, 
		v.z + w.z 
	};
}

template<typename T> Vector3T<T> operator-(const Vector3T<T>& v, const Vector3T<T>& w)
{
	return 
	{ 
		v.x - w.x,
		v.y - w.y, 
		v.z - w.z 
	};
}

// Vector-Scalar Multiplication - Use of Extra Template Parameter allows for Scalar Type to NOT MATCH Vector Type
template<typename T> Vector3T<T> operator*(const Vector3T<T>& v, FloatTypeFor<T> s)
{
	return 
	{ 
		static_cast<T>(v.x * s), 
		static_cast<T>(v.y * s), 
		static_cast<T>(v.z * s) 
	};
}
template<typename T> Vector3T<T> operator*(FloatTypeFor<T> s, const Vector3T<T>& v)
{
	return 
	{ 
		static_cast<T>(v.x * s), 
		static_cast<T>(v.y * s), 
		static_cast<T>(v.z * s) 
	};
}

//=======================
// Non-Member Functions
//=======================

// Dot Product of Two given Vectors (Order Not Important) - Non Member Version
template<typename T> T Dot(const Vector3T<T>& v, const Vector3T<T>& w)
{
	return
		v.x * w.x +
		v.y * w.y +
		v.z * w.z;
}

// Cross Product of Two given Vectors (Order is Important) - Non-Member Version
template<typename T> Vector3T<T> Cross(const Vector3T<T>& v, const Vector3T<T>& w)
{
	return
	{
		v.y * w.z - v.z * w.y,
		v.z * w.x - v.x * w.z,
		v.x * w.y - v.y * w.x
	};
}

// Return Unit Length Vector in SAME DIRECTION as the one given (NOT SUPPORTED FOR INT VECTORS: Vector3i
template<typename T> Vector3T<T> Normalise(const Vector3T<T>& v)
{
	T lengthSq = v.LengthSq();

	// Can't Normalise Zero Length Vector
	if (IsZero(lengthSq))
		return { 0,0,0 };

	T invLength = InvSqrt(lengthSq);
	return
	{
		v.x * invLength,
		v.y * invLength,
		v.z * invLength
	};
}

//=============================================================================================
// Template Instantiation
//=============================================================================================
// Instantiate this Template Class for specific Numeric Types. Prevents use of other Types
// and allows for Code to be placed in .cpp file
//=============================================================================================

template class Vector3T<float>;		// Vector3 / Vector3f
template class Vector3T<double>;	// Vector3d
template class Vector3T<int>;		// Vector3i

// Also need to Instaniate all Non-Member Template Functions
template Vector3 operator+(const Vector3& v, const Vector3& w);
template Vector3 operator-(const Vector3& v, const Vector3& w);
template Vector3 operator*(const Vector3& v, float s);
template Vector3 operator*(float s, const Vector3& v);
template Vector3 operator/(const Vector3&, float s);
template float Dot(const Vector3& v, const Vector3& w);
template Vector3 Cross(const Vector3& v, const Vector3& w);
template Vector3 Normalise(const Vector3& v);

template Vector3d operator+(const Vector3d& v, const Vector3d& w);
template Vector3d operator-(const Vector3d& v, const Vector3d& w);
template Vector3d operator*(const Vector3d& v, double s);
template Vector3d operator*(double s, const Vector3d& v);
template Vector3d operator/(const Vector3d&, double s);
template double Dot(const Vector3d& v, const Vector3d& w);
template Vector3d Cross(const Vector3d& v, const Vector3d& w);
template Vector3d Normalise(const Vector3d& v);

template Vector3i operator+(const Vector3i& v, const Vector3i& w);
template Vector3i operator-(const Vector3i& v, const Vector3i& w);
template Vector3i operator*(const Vector3i& v, float s);
template Vector3i operator*(float s, const Vector3i& v);
template Vector3i operator/(const Vector3i&, float s);
template int Dot(const Vector3i& v, const Vector3i& w);
template Vector3i Cross(const Vector3i& v, const Vector3i& w);