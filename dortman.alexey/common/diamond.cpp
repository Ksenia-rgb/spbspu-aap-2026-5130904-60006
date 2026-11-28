#include "diamond.hpp"
#include <stdexcept>

namespace dortman
{
  Diamond::Diamond(const point_t & pos, double horiz_diag, double vert_diag):
    pos_(pos),
    horiz_diag_(horiz_diag),
    vert_diag_(vert_diag)
  {
    if (horiz_diag_ <= 0.0 || vert_diag_ <= 0.0)
    {
      throw std::invalid_argument("Некорректные диагонали ромба");
    }
  }

  Diamond::Diamond(double horiz_diag, double vert_diag):
    Diamond({0.0, 0.0}, horiz_diag, vert_diag)
  {}

  double Diamond::getArea() const
  {
    const double half_factor = 0.5;
    return (horiz_diag_ * vert_diag_) * half_factor;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return {horiz_diag_, vert_diag_, pos_};
  }

  void Diamond::move(const point_t & pos)
  {
    pos_ = pos;
  }

  void Diamond::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Diamond::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
    }
    horiz_diag_ *= k;
    vert_diag_ *= k;
  }
}
