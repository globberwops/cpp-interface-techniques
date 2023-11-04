// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>             // for std::size_t
#include <gw/crtp.hpp>         // for gw::Crtp
#include <gw/strong_type.hpp>  // for gw::StrongType

namespace gw::cpp_interface_techniques::crtp {

using RoadId = gw::strong_type<struct RoadIdTag, size_t>;

template <typename Derived>
class IMap : private gw::crtp<IMap, Derived> {
 public:
  auto GetRoad(RoadId identifier) noexcept -> decltype(auto) { return this->self().GetRoad(identifier); }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> decltype(auto) {
    return this->self().GetRoad(identifier);
  }

  auto AddRoadFront() noexcept -> decltype(auto) { return this->self().AddRoadFront(); }

  auto AddRoadBack() noexcept -> decltype(auto) { return this->self().AddRoadBack(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
