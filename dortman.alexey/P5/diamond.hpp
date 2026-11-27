#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace dortman
{
  class Diamond: public Shape
  {
  public:
    Diamond(const point_t & pos, double horiz_diag, double vert_diag);
    Diamond(double horiz_diag, double vert_diag);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t pos_;
    double horiz_diag_;
    double vert_diag_;
  };
}

#endif
