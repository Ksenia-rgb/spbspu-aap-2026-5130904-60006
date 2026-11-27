#include "./ellipse.hpp"
#include "./geometry.hpp"

#include <stdexcept>

namespace sergeev
{
  Ellipse::Ellipse(const point_t &pos, double radiusX, double radiusY):
    pos_(pos),
    radiusX_(radiusX),
    radiusY_(radiusY)
  {
    if (!isFinite(pos) || !isPositive(radiusX) || !isPositive(radiusY))
    {
      throw std::invalid_argument("Invalid ellipse");
    }
  }

  double Ellipse::getArea() const
  {
    const double pi = 3.14159265358979323846;
    return pi * radiusX_ * radiusY_;
  }

  rectangle_t Ellipse::getFrameRect() const
  {
    const double diameterFactor = 2.0;
    return {pos_, diameterFactor * radiusX_, diameterFactor * radiusY_};
  }

  void Ellipse::move(const point_t &pos)
  {
    if (!isFinite(pos))
    {
      throw std::invalid_argument("Invalid position");
    }
    pos_ = pos;
  }

  void Ellipse::move(double dx, double dy)
  {
    move({pos_.x + dx, pos_.y + dy});
  }

  void sergeev::Ellipse::scale(double factor)
  {
    if (!isPositive(factor))
    {
      throw std::invalid_argument("Invalid scale factor");
    }
    const double radiusX = radiusX_ * factor;
    const double radiusY = radiusY_ * factor;
    if (!isPositive(radiusX) || !isPositive(radiusY))
    {
      throw std::overflow_error("Invalid scaled ellipse radii");
    }
    radiusX_ = radiusX;
    radiusY_ = radiusY;
  }

}
