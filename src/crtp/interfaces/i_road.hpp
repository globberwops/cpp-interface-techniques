// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>             // for std::size_t
#include <gw/crtp.hpp>         // for gw::Crtp
#include <gw/strong_type.hpp>  // for gw::StrongType

namespace gw::cpp_interface_techniques::crtp {

using LaneId = gw::StrongType<size_t, struct LaneIdTag>;

template <typename Derived>
class IRoad : private gw::Crtp<IRoad, Derived> {
 public:
  auto GetLane(LaneId identifier) noexcept -> decltype(auto) { return this->Self().GetLane(identifier); }

  [[nodiscard]] auto GetLane(LaneId identifier) const noexcept -> decltype(auto) {
    return this->Self().GetLane(identifier);
  }

  auto AddLaneLeft() noexcept -> decltype(auto) { return this->Self().AddLaneLeft(); }

  auto AddLaneRight() noexcept -> decltype(auto) { return this->Self().AddLaneRight(); }

  auto GetNextRoad() noexcept -> Derived& { return this->Self().GetNextRoad(); }

  [[nodiscard]] auto GetNextRoad() const noexcept -> const Derived& { return this->Self().GetNextRoad(); }

  auto GetPreviousRoad() noexcept -> Derived& { return this->Self().GetPreviousRoad(); }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> const Derived& { return this->Self().GetPreviousRoad(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
