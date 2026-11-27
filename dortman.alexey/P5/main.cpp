#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "diamond.hpp"
#include "ring.hpp"

namespace dortman
{
  void scaleShapeAroundPoint(Shape & shape, const point_t & anchor, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
    }

    const point_t old_center = shape.getFrameRect().pos;
    const double dx = anchor.x - old_center.x;
    const double dy = anchor.y - old_center.y;

    shape.move(anchor);
    shape.scale(k);
    shape.move(-dx * k, -dy * k);
  }

  void scaleAll(Shape * const * shapes, size_t count, const point_t & anchor, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
    }

    for (size_t i = 0; i < count; ++i)
    {
      scaleShapeAroundPoint(*shapes[i], anchor, k);
    }
  }

  double getTotalArea(const Shape * const * shapes, size_t count)
  {
    double total = 0.0;
    for (size_t i = 0; i < count; ++i)
    {
      total += shapes[i]->getArea();
    }
    return total;
  }

  rectangle_t getTotalFrameRect(const Shape * const * shapes, size_t count)
  {
    if (count == 0)
    {
      return {0.0, 0.0, {0.0, 0.0}};
    }

    const double half = 0.5;
    const rectangle_t first = shapes[0]->getFrameRect();
    double min_x = first.pos.x - first.width * half;
    double max_x = first.pos.x + first.width * half;
    double min_y = first.pos.y - first.height * half;
    double max_y = first.pos.y + first.height * half;

    for (size_t i = 1; i < count; ++i)
    {
      const rectangle_t rect = shapes[i]->getFrameRect();
      const double left = rect.pos.x - rect.width * half;
      const double right = rect.pos.x + rect.width * half;
      const double bottom = rect.pos.y - rect.height * half;
      const double top = rect.pos.y + rect.height * half;

      if (left < min_x)
      {
        min_x = left;
      }
      if (right > max_x)
      {
        max_x = right;
      }
      if (bottom < min_y)
      {
        min_y = bottom;
      }
      if (top > max_y)
      {
        max_y = top;
      }
    }

    const double total_width = max_x - min_x;
    const double total_height = max_y - min_y;
    const point_t center = {min_x + total_width * half, min_y + total_height * half};
    return {total_width, total_height, center};
  }

  void printRect(std::ostream & out, const rectangle_t & rect)
  {
    out << "центр=(" << rect.pos.x << ", " << rect.pos.y << "), "
        << "ширина=" << rect.width << ", высота=" << rect.height;
  }

  void printReport(std::ostream & out, const Shape * const * shapes, size_t count)
  {
    for (size_t i = 0; i < count; ++i)
    {
      out << "Фигура #" << (i + 1) << ": площадь=" << shapes[i]->getArea() << ", рамка=[";
      printRect(out, shapes[i]->getFrameRect());
      out << "]\n";
    }

    out << "Суммарная площадь: " << getTotalArea(shapes, count) << "\n";
    out << "Общий ограничивающий прямоугольник: [";
    printRect(out, getTotalFrameRect(shapes, count));
    out << "]\n";
  }

  void clearShapes(Shape ** shapes, size_t count) noexcept
  {
    for (size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
  }
}

int main()
{
  const size_t shapes_count = 6;
  dortman::Shape * shapes[shapes_count] = {};
  size_t created = 0;

  const dortman::point_t rect_pos = {2.0, 3.0};
  const double rect_w1 = 4.0;
  const double rect_h1 = 6.0;
  const double rect_w2 = 5.0;
  const double rect_h2 = 2.0;

  const dortman::point_t diamond_pos = {-1.0, 4.0};
  const double diamond_d1_a = 6.0;
  const double diamond_d2_a = 8.0;
  const double diamond_d1_b = 4.0;
  const double diamond_d2_b = 10.0;

  const dortman::point_t ring_pos = {3.0, -2.0};
  const double ring_outer1 = 5.0;
  const double ring_inner1 = 2.0;
  const double ring_outer2 = 4.0;
  const double ring_inner2 = 1.0;

  try
  {
    shapes[created++] = new dortman::Rectangle(rect_pos, rect_w1, rect_h1);
    shapes[created++] = new dortman::Rectangle(rect_w2, rect_h2);
    shapes[created++] = new dortman::Diamond(diamond_pos, diamond_d1_a, diamond_d2_a);
    shapes[created++] = new dortman::Diamond(diamond_d1_b, diamond_d2_b);
    shapes[created++] = new dortman::Ring(ring_pos, ring_outer1, ring_inner1);
    shapes[created++] = new dortman::Ring(ring_outer2, ring_inner2);
  }
  catch (const std::exception & e)
  {
    dortman::clearShapes(shapes, created);
    std::cerr << "Ошибка создания фигур: " << e.what() << "\n";
    return 1;
  }

  std::cout << "--- До масштабирования ---\n";
  dortman::printReport(std::cout, shapes, shapes_count);

  double anchor_x = 0.0;
  double anchor_y = 0.0;
  double scale_factor = 0.0;

  if (!(std::cin >> anchor_x >> anchor_y >> scale_factor))
  {
    dortman::clearShapes(shapes, shapes_count);
    std::cerr << "Некорректный ввод параметров масштабирования\n";
    return 1;
  }

  if (scale_factor <= 0.0)
  {
    dortman::clearShapes(shapes, shapes_count);
    std::cerr << "Коэффициент масштабирования должен быть положительным\n";
    return 1;
  }

  try
  {
    dortman::scaleAll(shapes, shapes_count, {anchor_x, anchor_y}, scale_factor);
  }
  catch (const std::exception & e)
  {
    dortman::clearShapes(shapes, shapes_count);
    std::cerr << "Ошибка масштабирования: " << e.what() << "\n";
    return 1;
  }

  std::cout << "\n--- После масштабирования ---\n";
  dortman::printReport(std::cout, shapes, shapes_count);

  dortman::clearShapes(shapes, shapes_count);
  return 0;
}
