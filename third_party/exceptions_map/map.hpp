// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <deque>  // for std::deque

#include "exceptions_map/road.hpp"  // for exceptions_map::Road

namespace gw::cpp_interface_techniques::exceptions_map {

class Map {
 public:
  auto GetRoad(size_t index) -> Road& { return roads_.at(index); }

  [[nodiscard]] auto GetRoad(size_t index) const -> const Road& { return roads_.at(index); }

  auto AddRoadFront() noexcept -> Road& {
    auto& road = roads_.emplace_front();

    if (roads_.size() > 1U) {
      auto& next_road = roads_.at(1U);
      road.SetNextRoad(next_road);
      next_road.SetPreviousRoad(road);
    }

    return road;
  }

  auto AddRoadBack() noexcept -> Road& {
    auto& road = roads_.emplace_back();

    if (roads_.size() > 1U) {
      auto& previous_road = roads_.at(roads_.size() - 2U);
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

}  // namespace gw::cpp_interface_techniques::exceptions_map
