#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "./shape.hpp"

namespace sergeev {
  class Ellipse: public Shape {
  public:
    Ellipse(const point_t& pos, double radiusX, double radiusY);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t pos_;
    double radiusX_, radiusY_;
  };
}

#endif
