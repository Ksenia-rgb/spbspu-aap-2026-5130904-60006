#include "ring.hpp"
#include <stdexcept>

namespace
{
  const double pi = 3.14159265358979323846;
}

namespace dortman
{
  Ring::Ring(const point_t & pos, double outer_radius, double inner_radius):
    pos_(pos),
    outer_radius_(outer_radius),
    inner_radius_(inner_radius)
  {
    if (inner_radius_ <= 0.0 || outer_radius_ <= inner_radius_)
    {
      throw std::invalid_argument("Некорректные радиусы кольца");
    }
  }

  Ring::Ring(double outer_radius, double inner_radius):
    Ring({0.0, 0.0}, outer_radius, inner_radius)
  {}

  double Ring::getArea() const
  {
    return pi * (outer_radius_ * outer_radius_ - inner_radius_ * inner_radius_);
  }

  rectangle_t Ring::getFrameRect() const
  {
    const double diameter = 2.0 * outer_radius_;
    return {diameter, diameter, pos_};
  }

  void Ring::move(const point_t & pos)
  {
    pos_ = pos;
  }

  void Ring::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Ring::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
    }
    outer_radius_ *= k;
    inner_radius_ *= k;
  }
}
