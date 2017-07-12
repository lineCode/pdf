#pragma once
#include <pdf/config.h>
#include <pdf/units.h>

namespace pdf {

struct size {
public:
  units cx;
  units cy;

  constexpr size() noexcept = default;
  constexpr size(units cx, units cy) noexcept : cx(cx), cy(cy) {}
};

}  // namespace pdf