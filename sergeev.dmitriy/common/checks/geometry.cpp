#include "geometry.hpp"

#include <limits>

namespace sergeev {
  static bool isFinite(const point_t& point)
  {
    const double maxValue = std::numeric_limits< double >::max();
    return (point.x >= -maxValue) && (point.x <= maxValue)
        && (point.y >= -maxValue) && (point.y <= maxValue);
  }

  static bool isPositive(double value)
  {
    const double maxValue = std::numeric_limits< double >::max();
    return (value > 0) && (value <= maxValue);
  }
}

