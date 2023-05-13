#include "pch.h"
#include "Geometry.h"
#include "clipper2/clipper.h"

Geometry::Polygon::Polygon(const std::vector<Vec2>& points)
{
    polyPoints = points;
}

bool Geometry::Polygon::isInside(const Vec2& point)
{
    return Clipper2Lib::PointInPolygon(Clipper2Lib::Point<float>(point.x, point.y), clipperPath) != Clipper2Lib::PointInPolygonResult::IsOutside;
}

bool Geometry::Polygon::isOutside(const Vec2& point)
{
    return !isInside(point);
}

void Geometry::Polygon::addPoint(const Vec2& point)
{
    polyPoints.push_back(point);
    clipperPath.push_back(Clipper2Lib::Point<float>(point.x, point.y));
}

void Geometry::Polygon::addPoint(const Vec3& point)
{
    addPoint(point.to2D());
}

std::vector<Vec2> Geometry::Polygon::getPoints()
{
    return polyPoints;
}

Geometry::Rectangle::Rectangle(const Vec2& start, const Vec2& end, float width)
{
    Vec2 direction{ (end - start).normalized() };
    Vec2 perpendicular{ direction.perpendicular() };

    this->addPoint(perpendicular * width + start);
    this->addPoint(perpendicular * width - start);
    this->addPoint(perpendicular * width + end);
    this->addPoint(perpendicular * width - end);
}

Geometry::Circle::Circle(const Vec2& center, float radius, int circlePoints)
{
    float outRadius{ radius / std::cos(2 * M_PI / circlePoints) };

    for (int i{ 1 }; i <= circlePoints; ++i)
    {
        float angle{ i * 2.0f * M_PI / circlePoints };
        this->addPoint(Vec2(center.x + outRadius * std::cos(angle), center.y + outRadius * std::sin(angle)));
    }
}
