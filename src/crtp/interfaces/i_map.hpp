// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>             // for std::size_t
#include <gw/crtp.hpp>         // for gw::Crtp
#include <gw/strong_type.hpp>  // for gw::StrongType

namespace gw::cpp_interface_techniques::crtp {

using RoadId = gw::StrongType<size_t, struct RoadIdTag>;

template <typename Derived>
class IMap : private gw::Crtp<IMap, Derived> {
 public:
  auto GetRoad(RoadId identifier) noexcept -> decltype(auto) { return this->Self().GetRoad(identifier); }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> decltype(auto) {
    return this->Self().GetRoad(identifier);
  }

  auto AddRoadFront() noexcept -> decltype(auto) { return this->Self().AddRoadFront(); }

  auto AddRoadBack() noexcept -> decltype(auto) { return this->Self().AddRoadBack(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
