// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "crtp/adapters/exceptions_map/road_adapter.hpp"
#include "crtp/interfaces/i_map.hpp"
#include "exceptions_map/map.hpp"

namespace gw::cpp_interface_techniques::crtp::exceptions_map {

class MapAdapter : public IMap<MapAdapter> {
 public:
  explicit MapAdapter(gw::cpp_interface_techniques::exceptions_map::Map& map) noexcept : map_{map} {}

  auto GetRoad(RoadId identifier) noexcept -> std::optional<RoadAdapter> {
    try {
      return RoadAdapter{map_.get().GetRoad(identifier())};
    } catch (...) {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> std::optional<const RoadAdapter> {
    try {
      return RoadAdapter{map_.get().GetRoad(identifier())};
    } catch (...) {
      return std::nullopt;
    }
  }

  auto AddRoadFront() noexcept -> RoadAdapter { return RoadAdapter{map_.get().AddRoadFront()}; }

  auto AddRoadBack() noexcept -> RoadAdapter { return RoadAdapter{map_.get().AddRoadBack()}; }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::exceptions_map::Map> map_;
};

}  // namespace gw::cpp_interface_techniques::crtp::exceptions_map
