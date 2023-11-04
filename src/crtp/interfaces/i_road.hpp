// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>             // for std::size_t
#include <gw/crtp.hpp>         // for gw::Crtp
#include <gw/strong_type.hpp>  // for gw::StrongType

namespace gw::cpp_interface_techniques::crtp {

using LaneId = gw::strong_type<size_t, struct LaneIdTag>;

template <typename Derived>
class IRoad : private gw::crtp<IRoad, Derived> {
 public:
  auto GetLane(LaneId identifier) noexcept -> decltype(auto) { return this->self().GetLane(identifier); }

  [[nodiscard]] auto GetLane(LaneId identifier) const noexcept -> decltype(auto) {
    return this->self().GetLane(identifier);
  }

  auto AddLaneLeft() noexcept -> decltype(auto) { return this->self().AddLaneLeft(); }

  auto AddLaneRight() noexcept -> decltype(auto) { return this->self().AddLaneRight(); }

  auto GetNextRoad() noexcept -> Derived& { return this->self().GetNextRoad(); }

  [[nodiscard]] auto GetNextRoad() const noexcept -> const Derived& { return this->self().GetNextRoad(); }

  auto GetPreviousRoad() noexcept -> Derived& { return this->self().GetPreviousRoad(); }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> const Derived& { return this->self().GetPreviousRoad(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
