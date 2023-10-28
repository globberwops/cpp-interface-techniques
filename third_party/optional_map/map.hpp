#pragma once

#include <deque>       // for std::deque
#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "optional_map/road.hpp"  // for optional_map::Road

namespace optional_map {

class Map {
 public:
  auto GetRoad(size_t index) noexcept -> std::optional<std::reference_wrapper<Road>> {
    if (index >= roads_.size()) {
      return std::nullopt;
    }
    return roads_[index];
  }

  [[nodiscard]] auto GetRoad(size_t index) const -> std::optional<std::reference_wrapper<const Road>> {
    if (index >= roads_.size()) {
      return std::nullopt;
    }
    return roads_[index];
  }

  auto AddRoadFront() -> std::optional<std::reference_wrapper<Road>> {
    auto& road = roads_.emplace_front();

    if (roads_.size() > 1U) {
      auto& next_road = roads_.at(1U);
      road.SetNextRoad(next_road);
      next_road.SetPreviousRoad(road);
    }

    return road;
  }

  auto AddRoadBack() -> std::optional<std::reference_wrapper<Road>> {
    auto& road = roads_.emplace_back();

    if (roads_.size() > 1U) {
      auto& previous_road = roads_.at(roads_.size() - 2U);
      road.SetPreviousRoad(previous_road);
      previous_road.SetNextRoad(road);
    }

    return road;
  }

 private:
  std::deque<Road> roads_;
};

}  // namespace optional_map
