#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace dortman
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & pos, double width, double height);
    Rectangle(double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t pos_;
    double width_;
    double height_;
  };
}

#endif
