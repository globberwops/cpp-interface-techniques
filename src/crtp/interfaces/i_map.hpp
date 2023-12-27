// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>             // for std::size_t
#include <gw/crtp.hpp>         // for gw::crtp
#include <gw/strong_type.hpp>  // for gw::strong_type

namespace gw::cpp_interface_techniques::crtp {

using RoadId = gw::strong_type<std::size_t, struct RoadIdTag>;

template <typename Derived>
class IMap : public gw::crtp<IMap, Derived> {
 public:
  auto GetRoad(RoadId identifier) noexcept -> decltype(auto) { return this->self().GetRoad(identifier); }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> decltype(auto) {
    return this->self().GetRoad(identifier);
  }

  auto AddRoadFront() noexcept -> decltype(auto) { return this->self().AddRoadFront(); }

  auto AddRoadBack() noexcept -> decltype(auto) { return this->self().AddRoadBack(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
