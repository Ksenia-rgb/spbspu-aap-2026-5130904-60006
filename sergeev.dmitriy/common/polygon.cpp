#include "./polygon.hpp"
#include "./geometry.hpp"

#include <limits>
#include <stdexcept>

namespace sergeev
{
  Polygon::Polygon(const Polygon &other):
    count_(other.count_),
    vertices_(new point_t[count_]),
    pos_(other.pos_)
  {
    for (size_t i = 0; i < count_; ++i)
    {
      vertices_[i] = other.vertices_[i];
    }
  }

  Polygon::Polygon(const point_t *vertices, size_t count):
    count_(count),
    vertices_(nullptr),
    pos_{0, 0}
  {
    const size_t minVertices = 3;
    if (!vertices || (count_ < minVertices))
    {
      throw std::invalid_argument("Polygon requires at least three vertices");
    }
    vertices_ = new point_t[count_];
    try
    {
      for (size_t i = 0; i < count_; ++i)
      {
        if (!isFinite(vertices[i]))
        {
          throw std::invalid_argument("Invalid polygon vertex");
        }
        vertices_[i] = {vertices[i].x - vertices[0].x, vertices[i].y - vertices[0].y};
      }
      const point_t center = getCentroid();
      pos_ = {vertices[0].x + center.x, vertices[0].y + center.y};
      if (!isFinite(pos_))
      {
        throw std::invalid_argument("Invalid polygon centroid");
      }
      for (size_t i = 0; i < count_; ++i)
      {
        vertices_[i].x -= center.x;
        vertices_[i].y -= center.y;
      }
    }
    catch (...)
    {
      delete[] vertices_;
      throw;
    }
  }

  Polygon::~Polygon()
  {
    delete[] vertices_;
  }

  Polygon &Polygon::operator=(const Polygon &other)
  {
    if (this != &other)
    {
      point_t *const vertices = new point_t[other.count_];
      for (size_t i = 0; i < other.count_; ++i)
      {
        vertices[i] = other.vertices_[i];
      }
      delete[] vertices_;
      vertices_ = vertices;
      count_ = other.count_;
      pos_ = other.pos_;
    }
    return *this;
  }

  double Polygon::getArea() const
  {
    const double areaFactor = 0.5;
    const double doubleArea = getSignedDoubleArea();
    return (doubleArea < 0 ? -doubleArea : doubleArea) * areaFactor;
  }

  rectangle_t Polygon::getFrameRect() const
  {
    double min_x = vertices_[0].x;
    double max_x = min_x;
    double min_y = vertices_[0].y;
    double max_y = min_y;
    for (size_t i = 1; i < count_; ++i)
    {
      if (vertices_[i].x < min_x)
      {
        min_x = vertices_[i].x;
      }
      if (vertices_[i].x > max_x)
      {
        max_x = vertices_[i].x;
      }
      if (vertices_[i].y < min_y)
      {
        min_y = vertices_[i].y;
      }
      if (vertices_[i].y > max_y)
      {
        max_y = vertices_[i].y;
      }
    }
    const double half = 0.5;
    const double width = max_x - min_x;
    const double height = max_y - min_y;
    const point_t center{pos_.x + min_x + width * half, pos_.y + min_y + height * half};
    return {center, width, height};
  }

  void Polygon::move(const point_t &pos)
  {
    if (!isFinite(pos))
    {
      throw std::invalid_argument("Invalid position");
    }
    pos_ = pos;
  }

  void Polygon::move(double dx, double dy)
  {
    move({pos_.x + dx, pos_.y + dy});
  }

  void Polygon::scale(double factor)
  {
    if (!isPositive(factor))
    {
      throw std::invalid_argument("Invalid scale factor");
    }
    for (size_t i = 0; i < count_; ++i)
    {
      const point_t vertex{vertices_[i].x * factor, vertices_[i].y * factor};
      if (!isFinite(vertex))
      {
        throw std::overflow_error("Invalid scaled polygon vertex");
      }
    }
    for (size_t i = 0; i < count_; ++i)
    {
      vertices_[i].x *= factor;
      vertices_[i].y *= factor;
    }
  }

  double Polygon::getSignedDoubleArea() const
  {
    double sum = 0;
    for (size_t i = 0; i < count_; ++i)
    {
      const point_t &current = vertices_[i];
      const point_t &next = vertices_[(i + 1) % count_];
      sum += current.x * next.y - next.x * current.y;
    }
    return sum;
  }

  point_t Polygon::getCentroid() const
  {
    const double doubleArea = getSignedDoubleArea();
    const double absoluteArea = doubleArea < 0 ? -doubleArea : doubleArea;
    if (!isPositive(absoluteArea))
    {
      throw std::invalid_argument("Polygon must have a nonzero finite area");
    }
    point_t center{0, 0};
    for (size_t i = 0; i < count_; ++i)
    {
      const point_t &current = vertices_[i];
      const point_t &next = vertices_[(i + 1) % count_];
      const double cross = current.x * next.y - next.x * current.y;
      center.x += (current.x + next.x) * cross;
      center.y += (current.y + next.y) * cross;
    }
    const double centroidFactor = 3.0;
    center.x /= centroidFactor * doubleArea;
    center.y /= centroidFactor * doubleArea;
    return center;
  }
}
