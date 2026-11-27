#include "./ellipse.hpp"
#include "./geometry.hpp"

#include <stdexcept>

namespace sergeev
{
  Ellipse::Ellipse(const point_t &pos, double radius_x, double radius_y):
    pos_(pos),
    radius_x_(radius_x),
    radius_y_(radius_y)
  {
    if (!isFinite(pos) || !isPositive(radius_x) || !isPositive(radius_y))
    {
      throw std::invalid_argument("Invalid ellipse");
    }
  }

  double Ellipse::getArea() const
  {
    const double pi = 3.14159265358979323846;
    return pi * radius_x_ * radius_y_;
  }

  rectangle_t Ellipse::getFrameRect() const
  {
    const double diameterFactor = 2.0;
    return {pos_, diameterFactor * radius_x_, diameterFactor * radius_y_};
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
    const double radius_x = radius_x_ * factor;
    const double radius_y = radius_y_ * factor;
    if (!isPositive(radius_x) || !isPositive(radius_y))
    {
      throw std::overflow_error("Invalid scaled ellipse radii");
    }
    radius_x_ = radius_x;
    radius_y_ = radius_y;
  }

}
