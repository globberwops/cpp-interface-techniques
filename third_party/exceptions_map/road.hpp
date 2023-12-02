// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <deque>       // for std::deque
#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional
#include <stdexcept>   // for std::runtime_error

#include "exceptions_map/lane.hpp"  // for exceptions_map::Lane

namespace gw::cpp_interface_techniques::exceptions_map {

class Road {
 public:
  auto GetLane(size_t index) -> decltype(auto) { return lanes_.at(index); }

  [[nodiscard]] auto GetLane(size_t index) const { return lanes_.at(index); }

  auto AddLaneLeft() noexcept -> decltype(auto) {
    decltype(auto) lane = lanes_.emplace_front();

    if (std::size(lanes_) > 1U) {
      decltype(auto) right_lane = lanes_.at(1U);
      lane.SetRightLane(right_lane);
      right_lane.SetLeftLane(lane);
    }

    return lane;
  }

  auto AddLaneRight() noexcept -> decltype(auto) {
    decltype(auto) lane = lanes_.emplace_back();

    if (std::size(lanes_) > 1U) {
      decltype(auto) left_lane = lanes_.at(std::size(lanes_) - 2U);
      lane.SetLeftLane(left_lane);
      left_lane.SetRightLane(lane);
    }

    return lane;
  }

  [[nodiscard]] auto GetNextRoad() -> decltype(auto) {
    return next_road_.has_value() ? next_road_.value().get() : throw std::runtime_error("No next road");
  }

  [[nodiscard]] auto GetNextRoad() const -> decltype(auto) {
    return next_road_.has_value() ? next_road_.value().get() : throw std::runtime_error("No next road");
  }

  [[nodiscard]] auto GetPreviousRoad() -> decltype(auto) {
    return previous_road_.has_value() ? previous_road_.value().get() : throw std::runtime_error("No previous road");
  }

  [[nodiscard]] auto GetPreviousRoad() const -> decltype(auto) {
    return previous_road_.has_value() ? previous_road_.value().get() : throw std::runtime_error("No previous road");
  }

  auto operator==(const Road& other) const -> bool { return &other == this; }

  auto operator!=(const Road& other) const -> bool { return &other != this; }

 private:
  friend class Map;

  void SetNextRoad(Road& next_road) { next_road_ = next_road; }

  void SetPreviousRoad(Road& previous_road) { previous_road_ = previous_road; }

  std::deque<Lane> lanes_;

  std::optional<std::reference_wrapper<Road>> next_road_{};
  std::optional<std::reference_wrapper<Road>> previous_road_{};
};

}  // namespace gw::cpp_interface_techniques::exceptions_map
