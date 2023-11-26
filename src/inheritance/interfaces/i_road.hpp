// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <gw/strong_type.hpp>  // for gw::StrongType
#include <memory>              // for std::unique_ptr

#include "inheritance/interfaces/i_lane.hpp"  // for gw::cpp_interface_techniques::inheritance::ILane

namespace gw::cpp_interface_techniques::inheritance {

using LaneId = gw::strong_type<struct LaneIdTag, size_t>;

class IRoad {
 public:
  virtual ~IRoad() = default;

  virtual auto GetLane(LaneId identifier) noexcept -> std::unique_ptr<ILane> = 0;

  [[nodiscard]] virtual auto GetLane(LaneId identifier) const noexcept -> std::unique_ptr<const ILane> = 0;

  virtual auto AddLaneLeft() noexcept -> std::unique_ptr<ILane> = 0;

  virtual auto AddLaneRight() noexcept -> std::unique_ptr<ILane> = 0;

  virtual auto GetNextRoad() noexcept -> std::unique_ptr<IRoad> = 0;

  [[nodiscard]] virtual auto GetNextRoad() const noexcept -> std::unique_ptr<const IRoad> = 0;

  virtual auto GetPreviousRoad() noexcept -> std::unique_ptr<IRoad> = 0;

  [[nodiscard]] virtual auto GetPreviousRoad() const noexcept -> std::unique_ptr<const IRoad> = 0;

  virtual auto operator==(const IRoad& other) const noexcept -> bool = 0;
  virtual auto operator!=(const IRoad& other) const noexcept -> bool = 0;
};

inline auto operator==(const std::unique_ptr<IRoad>& lhs, const std::unique_ptr<IRoad>& rhs) noexcept -> bool {
  return *lhs == *rhs;
}

inline auto operator!=(const std::unique_ptr<IRoad>& lhs, const std::unique_ptr<IRoad>& rhs) noexcept -> bool {
  return !(*lhs == *rhs);
}

}  // namespace gw::cpp_interface_techniques::inheritance
