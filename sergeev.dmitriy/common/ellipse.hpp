#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "./shape.hpp"

namespace sergeev
{
  class Ellipse: public Shape
  {
  public:
    Ellipse(const point_t &pos, double radius_x, double radius_y);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t pos_;
    double radius_x_, radius_y_;
  };
}

#endif
