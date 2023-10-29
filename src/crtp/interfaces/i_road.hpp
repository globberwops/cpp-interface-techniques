// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>  // for size_t

#include "strong_type/strong_type.hpp"

namespace gw::cpp_interface_techniques::crtp {

using LaneId = gw::StrongType<size_t, struct LaneIdTag>;

template <typename Derived>
class IRoad {
 public:
  auto GetLane(LaneId identifier) noexcept -> decltype(auto) { return Self().GetLane(identifier); }

  [[nodiscard]] auto GetLane(LaneId identifier) const noexcept -> decltype(auto) { return Self().GetLane(identifier); }

  auto AddLaneLeft() noexcept -> decltype(auto) { return Self().AddLaneLeft(); }

  auto AddLaneRight() noexcept -> decltype(auto) { return Self().AddLaneRight(); }

  auto GetNextRoad() noexcept -> Derived& { return Self().GetNextRoad(); }

  [[nodiscard]] auto GetNextRoad() const noexcept -> const Derived& { return Self().GetNextRoad(); }

  auto GetPreviousRoad() noexcept -> Derived& { return Self().GetPreviousRoad(); }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> const Derived& { return Self().GetPreviousRoad(); }

 private:
  constexpr auto Self() noexcept -> Derived& { return static_cast<Derived&>(*this); }
  constexpr auto Self() const noexcept -> const Derived& { return static_cast<const Derived&>(*this); }
};

}  // namespace gw::cpp_interface_techniques::crtp
