#pragma once

#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace math
{
	/*  See
		https://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/
		for the potential portability problems with the union and bit-fields below.
	*/
	union Float_t
	{
		Float_t(float num = 0.0f) : f(num) {}
		// Portable extraction of components.
		[[nodiscard]] bool Negative() const { return i < 0; }
		[[nodiscard]] int32_t RawMantissa() const { return i & ((1 << 23) - 1); }
		[[nodiscard]] int32_t RawExponent() const { return (i >> 23) & 0xFF; }

		int32_t i;
		float f;
#ifdef _DEBUG
		struct
		{   // Bitfields for exploration. Do not use in production code.
			uint32_t mantissa : 23;
			uint32_t exponent : 8;
			uint32_t sign : 1;
		} parts;
#endif
	};

	bool IsZero(float A);
	bool NearEqual(float A, float B, int maxUlpsDiff = 4);
}

struct IntersectionResultVec2;
struct IntersectionResultVec3;
struct ProjectionInfo;
class Vec3;

class Vec2
{
public:
	float x, y;
	Vec2() { x = y = 0.f; };
	Vec2(float x, float y) : x(x), y(y) {};

	[[nodiscard]] Vec2					 operator+(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator+(float f) const;
	[[nodiscard]] Vec2					 operator+=(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator+=(float f) const;
	[[nodiscard]] Vec2					 operator-(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator-(float f) const;
	[[nodiscard]] Vec2					 operator-=(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator-=(float f) const;
	[[nodiscard]] Vec2					 operator*(float f) const;
	[[nodiscard]] Vec2					 operator*(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator*=(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator*=(float f) const;
	[[nodiscard]] Vec2					 operator/(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator/(float f) const;
	[[nodiscard]] Vec2					 operator/=(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator/=(float f) const;
	[[nodiscard]] bool					 operator==(const Vec2& v) const;
	[[nodiscard]] bool					 operator!=(const Vec2& v) const;

	[[nodiscard]] bool					 isValid() const;
	[[nodiscard]] bool					 isVisibleOnScreen() const;
	[[nodiscard]] float					 length() const;
	[[nodiscard]] float					 lengthSquared() const;
	[[nodiscard]] float					 distance(const Vec2& o) const;
	[[nodiscard]] float					 distanceSquared(const Vec2& o) const;
	[[nodiscard]] Vec2					 vScale(const Vec2& s) const;
	[[nodiscard]] Vec2					 scale(float s) const;
	[[nodiscard]] Vec2					 normalized() const;
	[[nodiscard]] Vec2					 perpendicular() const;
	[[nodiscard]] Vec2					 append(const Vec2& pos1, Vec2& pos2, float dist) const;
	[[nodiscard]] Vec2					 rotated(float angle) const;
	[[nodiscard]] Vec2					 clone() const;
	[[nodiscard]] float					 polar() const;
	[[nodiscard]] float					 crossProduct(const Vec2& other) const;
	[[nodiscard]] float					 angleBetween(const Vec2& o) const;
	[[nodiscard]] IntersectionResultVec2 intersection(const Vec2& lineSegment1End, Vec2& lineSegment2Start, Vec2& lineSegment2End) const;
	[[nodiscard]] ProjectionInfo		 projectOn(const Vec2& segmentStart, Vec2& segmentEnd) const;
	[[nodiscard]] Vec2					 extend(const Vec2& to, float distance) const;
	[[nodiscard]] Vec3					 to3D(float height = 0) const;
	[[nodiscard]] std::string			 toString() const;
};

class Vec3
{
public:
	float x, y, z;
	Vec3() { x = y = z = 0.f; };
	Vec3(float x, float y, float z = 0) : x(x), y(y), z(z) {};

	[[nodiscard]] Vec3					operator+(const Vec3& v) const;
	[[nodiscard]] Vec3					operator+(float f) const;
	[[nodiscard]] Vec3					operator+=(const Vec3& v) const;
	[[nodiscard]] Vec3					operator+=(float f) const;
	[[nodiscard]] Vec3					operator-(const Vec3& v) const;
	[[nodiscard]] Vec3					operator-(float f) const;
	[[nodiscard]] Vec3					operator-=(const Vec3& v) const;
	[[nodiscard]] Vec3					operator-=(float f) const;
	[[nodiscard]] Vec3					operator*(const Vec3& v) const;
	[[nodiscard]] Vec3					operator*(float f) const;
	[[nodiscard]] Vec3					operator*=(const Vec3& v) const;
	[[nodiscard]] Vec3					operator*=(float f) const;
	[[nodiscard]] Vec3					operator/(const Vec3& v) const;
	[[nodiscard]] Vec3					operator/(float f) const;
	[[nodiscard]] Vec3					operator/=(const Vec3& v) const;
	[[nodiscard]] Vec3					operator/=(float f) const;
	[[nodiscard]] bool					operator!=(const Vec3& v) const;
	[[nodiscard]] bool					operator==(const Vec3& v) const;

	[[nodiscard]] bool					isValid() const;
	[[nodiscard]] bool					isOnScreen(int tolerance = 0) const;
	[[nodiscard]] Vec3					switchYZ() const;
	[[nodiscard]] Vec3					negate() const;
	[[nodiscard]] float					dotProduct(const Vec3& other) const;
	[[nodiscard]] float					crossProduct(const Vec3& other) const;
	[[nodiscard]] float					polar() const;
	[[nodiscard]] float					angleBetween(const Vec3& other) const;
	[[nodiscard]] bool					close(float a, float b, float eps) const;
	[[nodiscard]] Vec3					rotated(float angle) const;
	[[nodiscard]] Vec3					perpendicular() const;
	[[nodiscard]] Vec3					append(const Vec3& pos1, Vec3& pos2, float dist) const;
	[[nodiscard]] Vec3					clone() const;
	[[nodiscard]] float					length() const;
	[[nodiscard]] float					lengthSquared() const;
	[[nodiscard]] float					distance(const Vec3& to) const;
	[[nodiscard]] float					distanceSquared(const Vec3& to) const;
	[[nodiscard]] Vec3					extend(const Vec3& to, float distance) const;
	[[nodiscard]] Vec3					scale(float s) const;
	[[nodiscard]] Vec3					rotate(const Vec3& startPos, float theta) const;
	[[nodiscard]] Vec3					rotateX(float angle) const;
	[[nodiscard]] Vec3					rotateY(float angle) const;
	[[nodiscard]] Vec3					rotateZ(float angle) const;
	[[nodiscard]] Vec3					normalized() const;
	[[nodiscard]] Vec3					setHeight(float val = FLT_MIN) const;
	[[nodiscard]] Vec2					to2D() const;
	[[nodiscard]] std::string			toString() const;

	[[nodiscard]] bool					isUnderTower(bool ally, bool enemy) const;
	[[nodiscard]] bool					isOnFountain(bool ally = false) const;
};

struct ProjectionInfo
{
	bool isOnSegment;
	Vec2 linePoint;
	Vec2 segmentPoint;
};

struct IntersectionResultVec2
{
	int intersects;
	Vec2 intersectionPoint;
};

struct IntersectionResultVec3
{
	bool intersects;
	Vec3 intersectionPoint;
};