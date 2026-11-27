#include "./rectangle.hpp"

#include <limits>
#include <stdexcept>


namespace sergeev
{
  static bool isFinite(const point_t& point)
  {
    const double maxValue = std::numeric_limits< double >::max();
    return (point.x >= -maxValue) && (point.x <= maxValue)
        && (point.y >= -maxValue) && (point.y <= maxValue);
  }

  static bool isPositive(double value)
  {
    const double maxValue = std::numeric_limits< double >::max();
    return (value > 0) && (value <= maxValue);
  }

  Rectangle::Rectangle(const point_t& pos, double width, double height):
    frame_{pos, width, height}{
      if (!isFinite(pos) || !isPositive(width) || !isPositive(height)) {
        throw std::invalid_argument("Invalid rectangle");
      }
    }
  Rectangle::Rectangle(double width, double height):
      Rectangle({0.0, 0.0}, width, height)
      {
      if (!isPositive(width) || !isPositive(height)) {
        throw std::invalid_argument("Invalid rectangle");
      }
    }

  double Rectangle::getArea() const
  {
    return frame_.width * frame_.height;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return frame_;
  }

  void Rectangle::move(const point_t shift) noexcept {
    if (!isFinite(shift)) {
      throw std::invalid_argument("Invalid position");
    }
    frame_.pos.x += shift.x;
    frame_.pos.y += shift.y;
  }

  void Rectangle::move(double dx, double dy) noexcept {
    move({frame_.pos.x + dx, frame_.pos.y + dy});
  }

  void Rectangle::scale(double factor) {
    if (!isPositive(factor)) {
      throw std::invalid_argument("Invalid scale factor");
    }
    frame_.height *= factor;
    frame_.width *= factor;
  }
}