// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <deque>       // for std::deque
#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "optional_map/road.hpp"  // for optional_map::Road

namespace gw::cpp_interface_techniques::optional_map {

class Map {
 public:
  auto GetRoad(size_t index) noexcept -> std::optional<std::reference_wrapper<Road>> {
    if (index >= roads_.size()) {
      return std::nullopt;
    }
    return roads_[index];
  }

  [[nodiscard]] auto GetRoad(size_t index) const noexcept -> std::optional<std::reference_wrapper<const Road>> {
    if (index >= roads_.size()) {
      return std::nullopt;
    }
    return roads_[index];
  }

  auto AddRoadFront() noexcept -> std::reference_wrapper<Road> {
    auto& road = roads_.emplace_front();

    if (roads_.size() > 1U) {
      auto& next_road = roads_.at(1U);
      road.SetNextRoad(next_road);
      next_road.SetPreviousRoad(road);
    }

    return road;
  }

  auto AddRoadBack() noexcept -> std::reference_wrapper<Road> {
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

struct MapFactory {
  static constexpr auto kLaneWidth = 3.5;
  static constexpr auto kLaneLength = 100.0;

  static auto Create() noexcept -> Map {
    Map map;

    for (auto i = 0U; i <= 2; ++i) {
      auto road = map.AddRoadBack();

      for (auto j = 0U; j <= 2; ++j) {
        auto lane = road.get().AddLaneRight();
        lane.get().SetLength(kLaneLength);
        lane.get().SetWidth(kLaneWidth);
      }
    }

    return map;
  }
};

}  // namespace gw::cpp_interface_techniques::optional_map
