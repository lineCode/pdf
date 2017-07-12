#pragma once
#include <pdf/config.h>
#include <pdf/units.h>

namespace pdf {

struct point {
public:
  units x;
  units y;

  constexpr point() noexcept = default;
  constexpr point(units x, units y) noexcept : x(x), y(y) {}
};

}  // namespace pdf