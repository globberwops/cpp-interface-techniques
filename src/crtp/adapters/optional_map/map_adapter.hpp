// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "crtp/adapters/optional_map/road_adapter.hpp"
#include "crtp/interfaces/i_map.hpp"
#include "optional_map/map.hpp"

namespace gw::cpp_interface_techniques::crtp::optional_map {

class MapAdapter : public IMap<MapAdapter> {
 public:
  explicit MapAdapter(gw::cpp_interface_techniques::optional_map::Map& map) noexcept : map_{map} {}

  auto GetRoad(RoadId identifier) noexcept -> std::optional<RoadAdapter> {
    auto road = map_.get().GetRoad(*identifier);
    if (road) {
      return RoadAdapter{*road};
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> std::optional<const RoadAdapter> {
    auto road = map_.get().GetRoad(*identifier);
    if (road) {
      return RoadAdapter{*road};
    }
    return std::nullopt;
  }

  auto AddRoadFront() noexcept -> RoadAdapter { return RoadAdapter{map_.get().AddRoadFront()}; }

  auto AddRoadBack() noexcept -> RoadAdapter { return RoadAdapter{map_.get().AddRoadBack()}; }

  inline auto operator==(const MapAdapter& rhs) const noexcept -> bool { return map_.get() == rhs.map_.get(); }

  inline auto operator!=(const MapAdapter& rhs) const noexcept -> bool { return !(*this == rhs); }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::optional_map::Map> map_;
};

}  // namespace gw::cpp_interface_techniques::crtp::optional_map
