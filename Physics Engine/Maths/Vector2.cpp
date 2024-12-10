//=========================================================================================================
// Vector2.h: Encapsulates (x, y) Coordinates and Supporting Functions
// - Uses Template Functions to work on Integer, Float and Double Values
// Integer (Vector2i), Float(Vector2, Vector2i), Double(Vector2d)
//=========================================================================================================
// Explicit Non-Member Function Definitions found at end of .cpp file
//=========================================================================================================


#include "Vector2.h"

//=====================
// Member Operators
//=====================

// Addition of Another Vector to this one (e.g. Position += Velocity)
template<typename T> Vector2T<T>& Vector2T<T>::operator+=(const Vector2T<T>& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

// Subtraction of Another Vector from this one (e.g. Velocity -= Acceleration)
template<typename T> Vector2T<T>& Vector2T<T>::operator-=(const Vector2T<T>& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

// Negate this Vector (e.g. Velocity = -Velocity)
template<typename T> Vector2T<T>& Vector2T<T>::operator-()
{
	Vector2T<T> vOut = 
	{ 
		-x, 
		-y 
	};

	return vOut;
}

// Plus sign infront of Vector - Unary Positive and Usually does Nothing. 
// Included for Completeness to reduce error when using Plus Signs (e.g. Velocity = +Velocity)
template<typename T> Vector2T<T>& Vector2T<T>::operator+()
{
	Vector2T<T> vOut = 
	{ 
		x,
		y 
	};

	return vOut;
}

// Multiply Vector by Scalar
template<typename T> Vector2T<T>& Vector2T<T>::operator*=(FloatTypeFor<T> s)
{
	x = static_cast<T>(x * s);
	y = static_cast<T>(y * s);

	return *this;
}

// Divide Vector by Scalar
template<typename T> Vector2T<T>& Vector2T<T>::operator/=(FloatTypeFor<T> s)
{
	x = static_cast<T>(x / s);
	y = static_cast<T>(y / s);

	return *this;
}

//==========================
// Other Member Functions
//==========================

// Returns Length of a Vector
template<typename T> FloatTypeFor<T> Vector2T<T>::Length() const
{
	return static_cast<FloatTypeFor<T>>(std::sqrt(
		x * x +
		y * y
	));
}

// Returns Square Length of a Vector
template<typename T> FloatTypeFor<T> Vector2T<T>::LengthSq() const
{
	return static_cast<FloatTypeFor<T>>
		(
			x * x +
			y * y
		);
}


//=======================
// Non-Member Operators
//=======================

// Vector-Vector Addition
template<typename T> Vector2T<T> operator+(const Vector2T<T>& v, const Vector2T<T>& w)
{
	return 
	{
		v.x + w.x, 
		v.y + w.y 
	};
}

// Vector-Vector Subtraction
template<typename T> Vector2T<T> operator-(const Vector2T<T>& v, const Vector2T<T>& w)
{
	return 
	{
		v.x - w.x,
		v.y - w.y 
	};
}

// Vector-Scalar Multiplication - Use of Extra Template Parameter allows for Scalar Type to NOT MATCH Vector Type
template<typename T> Vector2T<T> operator*(const Vector2T<T>& v, FloatTypeFor<T> s)
{
	return 
	{
		static_cast<T>(v.x * s),
		static_cast<T>(v.y * s) 
	};
}
template<typename T> Vector2T<T> operator*(FloatTypeFor<T> s, const Vector2T<T>& v)
{
	return 
	{ 
		static_cast<T>(v.x * s), 
		static_cast<T>(v.y * s) 
	};
}

// Vector-Scalar Division - Use of Extra Template Parameter allows for Scalar Type to NOT MATCH Vector Type
template<typename T> Vector2T<T> operator/(const Vector2T<T> v, FloatTypeFor<T> s)
{
	return 
	{ 
		static_cast<T>(v.x / s), 
		static_cast<T>(v.y / s)
	};
}


//=======================
// Non-Member Functions
//=======================

// Dot Product of Two given Vectors (Order Not Important) - Non-Member Version
template<typename T> T Dot(const Vector2T<T>& v, const Vector2T<T>& w)
{
	return
		v.x * w.x +
		v.y * w.y;
}

// Return Unit Length Vector in SAME DIRECTION as give one (NOT SUPPORTED FOR INT VECTORS)
template<typename T> Vector2T<T> Normalise(const Vector2T<T>& v)
{
	T lengthSq = v.LengthSq();

	// Can't Normalise Zero Length Vector
	if (IsZero(lengthSq))
		return { 0,0 };

	T invLength = InvSqrt(lengthSq);
	return 
	{ 
		v.x * invLength,
		v.y * invLength 
	};
}

//=============================================================================================
// Template Instantiation
//=============================================================================================
// Instantiate this Template Class for specific Numeric Types. Prevents use of other Types
// and allows for Code to be placed in .cpp file
//=============================================================================================

template class Vector2T<float>;		// Vector2 / Vector2f
template class Vector2T<double>;	// Vector2d
template class Vector2T<int>;		// Vector2i

// Also need to Instantiate all Non-Member Template Functions
template Vector2 operator+(const Vector2& v, const Vector2& w);
template Vector2 operator-(const Vector2& v, const Vector2& w);
template Vector2 operator*(const Vector2& v, float s);
template Vector2 operator*(float s, const Vector2& v);
template Vector2 operator/(const Vector2& v, float s);
template float Dot(const Vector2& v, const Vector2& w);
template Vector2 Normalise(const Vector2& v);


template Vector2d operator+(const Vector2d& v, const Vector2d& w);
template Vector2d operator-(const Vector2d& v, const Vector2d& w);
template Vector2d operator*(const Vector2d& v, double s);
template Vector2d operator*(double s, const Vector2d& v);
template Vector2d operator/(const Vector2d& v, double s);
template double Dot(const Vector2d& v, const Vector2d& w);
template Vector2d Normalise(const Vector2d& v);


template Vector2i operator+(const Vector2i& v, const Vector2i& w);
template Vector2i operator-(const Vector2i& v, const Vector2i& w);
template Vector2i operator*(const Vector2i& v, float s);
template Vector2i operator*(float s, const Vector2i& v);
template Vector2i operator/(const Vector2i& v, float s);
template int Dot(const Vector2i& v, const Vector2i& w);
// Normalise Doesm't make sense for Vector2i (Integer Coordinates)