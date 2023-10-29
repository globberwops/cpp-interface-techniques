// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <deque>       // for std::deque
#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "optional_map/lane.hpp"  // for optional_map::Lane

namespace gw::cpp_interface_techniques::optional_map {

class Road {
 public:
  auto GetLane(size_t index) noexcept -> std::optional<std::reference_wrapper<Lane>> {
    if (index >= lanes_.size()) {
      return std::nullopt;
    }
    return lanes_[index];
  }

  [[nodiscard]] auto GetLane(size_t index) const noexcept -> std::optional<std::reference_wrapper<const Lane>> {
    if (index >= lanes_.size()) {
      return std::nullopt;
    }
    return lanes_[index];
  }

  auto AddLaneLeft() noexcept -> std::optional<std::reference_wrapper<Lane>> {
    auto& lane = lanes_.emplace_front();

    if (lanes_.size() > 1U) {
      auto& right_lane = lanes_.at(1U);
      lane.SetRightLane(right_lane);
      right_lane.SetLeftLane(lane);
    }

    return lane;
  }

  auto AddLaneRight() noexcept -> std::optional<std::reference_wrapper<Lane>> {
    auto& lane = lanes_.emplace_back();

    if (lanes_.size() > 1U) {
      auto& left_lane = lanes_.at(lanes_.size() - 2U);
      lane.SetLeftLane(left_lane);
      left_lane.SetRightLane(lane);
    }

    return lane;
  }

  [[nodiscard]] auto GetNextRoad() noexcept -> std::optional<std::reference_wrapper<Road>> { return next_road_; }

  [[nodiscard]] auto GetNextRoad() const noexcept -> std::optional<std::reference_wrapper<const Road>> {
    return next_road_;
  }

  [[nodiscard]] auto GetPreviousRoad() noexcept -> std::optional<std::reference_wrapper<Road>> {
    return previous_road_;
  }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> std::optional<std::reference_wrapper<const Road>> {
    return previous_road_;
  }

  auto operator==(const Road& other) const noexcept -> bool { return &other == this; }

  auto operator!=(const Road& other) const noexcept -> bool { return &other != this; }

 private:
  friend class Map;

  void SetNextRoad(std::optional<std::reference_wrapper<Road>> next_road) noexcept { next_road_ = next_road; }

  void SetPreviousRoad(std::optional<std::reference_wrapper<Road>> previous_road) noexcept {
    previous_road_ = previous_road;
  }

  std::deque<Lane> lanes_;

  std::optional<std::reference_wrapper<Road>> next_road_{};
  std::optional<std::reference_wrapper<Road>> previous_road_{};
};

}  // namespace gw::cpp_interface_techniques::optional_map