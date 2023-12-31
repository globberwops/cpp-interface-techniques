// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <deque>  // for std::deque

#include "exceptions_map/road.hpp"  // for exceptions_map::Road

namespace gw::cpp_interface_techniques::exceptions_map {

class Map {
 public:
  auto GetRoad(size_t index) -> decltype(auto) { return roads_.at(index); }

  [[nodiscard]] auto GetRoad(size_t index) const -> const Road& { return roads_.at(index); }

  auto AddRoadFront() noexcept -> decltype(auto) {
    decltype(auto) road = roads_.emplace_front();

    if (std::size(roads_) > 1U) {
      decltype(auto) next_road = roads_.at(1U);
      road.SetNextRoad(next_road);
      next_road.SetPreviousRoad(road);
    }

    return road;
  }

  auto AddRoadBack() noexcept -> decltype(auto) {
    decltype(auto) road = roads_.emplace_back();

    if (std::size(roads_) > 1U) {
      decltype(auto) previous_road = roads_.at(std::size(roads_) - 2U);
      road.SetPreviousRoad(previous_road);
      previous_road.SetNextRoad(road);
    }

    return road;
  }

  auto operator==(const Map& other) const noexcept -> bool { return &other == this; }

  auto operator!=(const Map& other) const noexcept -> bool { return &other != this; }

 private:
  std::deque<Road> roads_;
};

struct MapFactory {
  static constexpr auto kLaneWidth = 3.5;
  static constexpr auto kLaneLength = 100.0;

  static auto Create() noexcept -> Map {
    Map map;

    for (auto i = 0U; i <= 2; ++i) {
      decltype(auto) road = map.AddRoadBack();

      for (auto j = 0U; j <= 2; ++j) {
        decltype(auto) lane = road.AddLaneRight();
        lane.SetLength(kLaneLength);
        lane.SetWidth(kLaneWidth);
      }
    }

    return map;
  }
};

}  // namespace gw::cpp_interface_techniques::exceptions_map
