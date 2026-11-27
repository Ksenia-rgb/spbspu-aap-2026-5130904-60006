#include "./rectangle.hpp"
#include "./checks/geometry.hpp"

#include <limits>
#include <stdexcept>


namespace sergeev
{
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

  void Rectangle::move(const point_t& pos) noexcept {
    if (!isFinite(pos)) {
      throw std::invalid_argument("Invalid position");
    }
    frame_.pos = pos;
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