// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <cstddef>  // for size_t

#include "strong_type/strong_type.hpp"

namespace gw::cpp_interface_techniques::crtp {

using RoadId = gw::StrongType<size_t, struct RoadIdTag>;

template <typename Derived>
class IMap {
 public:
  auto GetRoad(RoadId identifier) noexcept -> decltype(auto) { return Self().GetRoad(identifier); }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> decltype(auto) { return Self().GetRoad(identifier); }

  auto AddRoadFront() noexcept -> decltype(auto) { return Self().AddRoadFront(); }

  auto AddRoadBack() noexcept -> decltype(auto) { return Self().AddRoadBack(); }

 private:
  constexpr auto Self() noexcept -> Derived& { return static_cast<Derived&>(*this); }
  constexpr auto Self() const noexcept -> const Derived& { return static_cast<const Derived&>(*this); }
};

}  // namespace gw::cpp_interface_techniques::crtp
