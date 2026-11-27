#include "./rectangle.hpp"

#include <stdexcept>

sergeev::Rectangle::Rectangle(const point_t& pos, double width, double height):
  frame_{pos, width, height}{
    if (frame_.width <= 0.0 || frame_.height <= 0.0)
    {
      throw std::invalid_argument("Некорректные размеры прямоугольника");
    }
  }
sergeev::Rectangle::Rectangle(double width, double height):
    Rectangle({0.0, 0.0}, width, height)
    {
    if (frame_.width <= 0.0 || frame_.height <= 0.0)
    {
      throw std::invalid_argument("Некорректные размеры прямоугольника");
    }
  }

double sergeev::Rectangle::getArea() const
{
  return frame_.width * frame_.height;
}


sergeev::rectangle_t sergeev::Rectangle::getFrameRect() const
{
  return frame_;
}

void sergeev::Rectangle::move(const point_t shift) noexcept {
  frame_.pos.x += shift.x;
  frame_.pos.y += shift.y;
}

void sergeev::Rectangle::move(double dx, double dy) noexcept {
  frame_.pos.x += dx;
  frame_.pos.y += dy;
}

void sergeev::Rectangle::scale(double factor) {
  if (factor <= 0.0) {
    throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
  }
  frame_.height *= factor;
  frame_.width *= factor;
}