#include <cstddef>
#include <exception>
#include <iostream>

#include "../common/ellipse.hpp"
#include "../common/polygon.hpp"
#include "../common/rectangle.hpp"

#include "../common/geometry.hpp"

namespace sergeev {
  static void printFrame(std::ostream& out, const rectangle_t& frame);
  static void scaleShapes(Shape* const* shapes, size_t count, const point_t& pos, double factor);
  static void printShapes(std::ostream& out, const Shape* const* shapes, size_t count);
}

void sergeev::printFrame(std::ostream& out, const rectangle_t& frame)
{
  out << "x: " << frame.pos.x << ", y: " << frame.pos.y;
  out << ", width: " << frame.width << ", height: " << frame.height << '\n';
}

void sergeev::scaleShapes(Shape* const* shapes, size_t count, const point_t& pos, double factor)
{
  if (!isFinite(pos) || !isPositive(factor)) {
    throw std::invalid_argument("Invalid scaling parameters");
  }
  for (size_t i = 0; i < count; ++i) {
    Shape& shape = *shapes[i];
    const point_t before = shape.getFrameRect().pos;
    shape.move(pos);
    const point_t after = shape.getFrameRect().pos;
    const double dx = before.x - after.x;
    const double dy = before.y - after.y;
    shape.scale(factor);
    shape.move(dx * factor, dy * factor);
  }
}

void sergeev::printShapes(std::ostream& out, const Shape* const* shapes, size_t count)
{
  if (count == 0) {
    throw std::invalid_argument("No shapes to print");
  }
  const rectangle_t first = shapes[0]->getFrameRect();
  const double half = 0.5;
  double minX = first.pos.x - first.width * half;
  double maxX = first.pos.x + first.width * half;
  double minY = first.pos.y - first.height * half;
  double maxY = first.pos.y + first.height * half;
  double totalArea = 0;
  for (size_t i = 0; i < count; ++i) {
    const Shape& shape = *shapes[i];
    const double area = shape.getArea();
    const rectangle_t frame = shape.getFrameRect();
    if (!isPositive(area) || !isFinite(frame.pos)
        || !isPositive(frame.width) || !isPositive(frame.height)) {
      throw std::overflow_error("Invalid shape dimensions or area");
    }
    totalArea += area;
    const double left = frame.pos.x - frame.width * half;
    if (left < minX) {
      minX = left;
    }
    const double right = frame.pos.x + frame.width * half;
    if (right > maxX) {
      maxX = right;
    }
    const double bottom = frame.pos.y - frame.height * half;
    if (bottom < minY) {
      minY = bottom;
    }
    const double top = frame.pos.y + frame.height * half;
    if (top > maxY) {
      maxY = top;
    }
    out << "Shape " << i + 1 << " area: " << area << '\n';
    out << "Frame: ";
    printFrame(out, frame);
  }
  const double width = maxX - minX;
  const double height = maxY - minY;
  const point_t center{minX + width * half, minY + height * half};
  if (!isFinite(center) || !isPositive(width)
      || !isPositive(height) || !isPositive(totalArea)) {
    throw std::overflow_error("Invalid total frame or area");
  }
  const rectangle_t totalFrame{center, width, height};
  out << "Total area: " << totalArea << '\n';
  out << "Total frame: ";
  printFrame(out, totalFrame);
}

int main() {
try {
    sergeev::Rectangle rect1({5.0, -0.3}, 10.0, 30.0);
    sergeev::Rectangle rect2({1.2, -2.14}, 5.0, 12.25);
    sergeev::Ellipse ellipse({-3.0, 2.0}, 3.0, 2.0);
    const sergeev::point_t vertices[] = {{0, 0}, {4, 0}, {4, 1}, {1, 1}, {1, 4}, {0, 4}};
    const size_t vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    sergeev::Polygon polygon(vertices, vertexCount);
    sergeev::Polygon polygonCopy(polygon);
    polygonCopy.move(-5.0, -5.0);
    sergeev::Shape* const shapes[] = {&rect1, &rect2, &ellipse, &polygon, &polygonCopy};
    const size_t count = sizeof(shapes) / sizeof(shapes[0]);

    std::cout << "Before scaling:\n";
    sergeev::printShapes(std::cout, shapes, count);
    sergeev::point_t pos{0, 0};
    double factor = 0;
    if (!(std::cin >> pos.x >> pos.y >> factor) || !sergeev::isFinite(pos)
        || !sergeev::isPositive(factor)) {
      std::cerr << "Invalid scaling parameters\n";
      return 1;
    }
    sergeev::scaleShapes(shapes, count, pos, factor);
    std::cout << "After scaling:\n";
    sergeev::printShapes(std::cout, shapes, count);
    if (!std::cout) {
      std::cerr << "Output error\n";
      return 2;
    }
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 2;
  }
  return 0;

}