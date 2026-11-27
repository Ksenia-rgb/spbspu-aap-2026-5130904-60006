#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cstddef>

#include "./shape.hpp"

namespace sergeev
{
  class Polygon: public Shape
  {
  public:
    Polygon(const Polygon &other);
    Polygon(const point_t *vertices, size_t count);
    ~Polygon() override;

    Polygon &operator=(const Polygon &other);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    size_t count_;
    point_t *vertices_;
    point_t pos_;
    double getSignedDoubleArea() const;
    point_t getCentroid() const;
  };
}

#endif
