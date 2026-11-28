#include "rectangle.hpp"
#include <stdexcept>

namespace dortman
{
  Rectangle::Rectangle(const point_t & pos, double width, double height):
    pos_(pos),
    width_(width),
    height_(height)
  {
    if (width_ <= 0.0 || height_ <= 0.0)
    {
      throw std::invalid_argument("Некорректные размеры прямоугольника");
    }
  }

  Rectangle::Rectangle(double width, double height):
    Rectangle({0.0, 0.0}, width, height)
  {}

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, pos_};
  }

  void Rectangle::move(const point_t & pos)
  {
    pos_ = pos;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
    }
    width_ *= k;
    height_ *= k;
  }
}
