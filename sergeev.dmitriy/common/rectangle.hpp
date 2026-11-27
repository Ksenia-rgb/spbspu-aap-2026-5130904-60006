#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP


#include "./shape.hpp"

namespace sergeev {
  class Rectangle : public Shape, rectangle_t {
  public:
    Rectangle(const point_t& pos, double width, double height);
    Rectangle(double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
  private:
    rectangle_t frame_;
  };
}


#endif // RECTANGLE_HPP
