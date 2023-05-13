#pragma once

namespace Geometry
{
	class Polygon
	{
	private:
		std::vector<Vec2> polyPoints{};
		Clipper2Lib::Path<float> clipperPath{};
	public:
		Polygon() {};
		Polygon(const std::vector<Vec2>& points);

		bool isInside(const Vec2& point);
		bool isOutside(const Vec2& point);

		void addPoint(const Vec2& point);
		void addPoint(const Vec3& point);

		std::vector<Vec2> getPoints();
	};

	class Rectangle : public Polygon
	{
		Rectangle() {};
		Rectangle(const Vec2& start, const Vec2& end, float width);
	};

	class Circle : public Polygon
	{
		Circle() {};
		Circle(const Vec2& center, float radius, int circlePoints = 32 );
	};

	class Ring : public Polygon
	{

	};

	class Cone : public Polygon
	{

	};
}