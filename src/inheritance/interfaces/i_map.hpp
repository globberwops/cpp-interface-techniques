// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <gw/strong_type.hpp>  // for gw::StrongType
#include <memory>              // for std::unique_ptr

#include "inheritance/interfaces/i_road.hpp"  // for gw::cpp_interface_techniques::inheritance::IRoad

namespace gw::cpp_interface_techniques::inheritance {

using RoadId = gw::strong_type<struct RoadIdTag, size_t>;

class IMap {
 public:
  virtual ~IMap() = default;

  virtual auto GetRoad(RoadId identifier) noexcept -> std::unique_ptr<IRoad> = 0;

  [[nodiscard]] virtual auto GetRoad(RoadId identifier) const noexcept -> std::unique_ptr<const IRoad> = 0;

  virtual auto AddRoadFront() noexcept -> std::unique_ptr<IRoad> = 0;

  virtual auto AddRoadBack() noexcept -> std::unique_ptr<IRoad> = 0;

  virtual auto operator==(const IMap& other) const noexcept -> bool = 0;
  virtual auto operator!=(const IMap& other) const noexcept -> bool = 0;
};

inline auto operator==(const std::unique_ptr<IMap>& lhs, const std::unique_ptr<IMap>& rhs) noexcept -> bool {
  return *lhs == *rhs;
}

inline auto operator!=(const std::unique_ptr<IMap>& lhs, const std::unique_ptr<IMap>& rhs) noexcept -> bool {
  return !(*lhs == *rhs);
}

}  // namespace gw::cpp_interface_techniques::inheritance
