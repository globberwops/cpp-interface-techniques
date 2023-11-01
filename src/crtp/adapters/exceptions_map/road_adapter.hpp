// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "crtp/adapters/exceptions_map/lane_adapter.hpp"
#include "crtp/interfaces/i_road.hpp"
#include "exceptions_map/road.hpp"

namespace gw::cpp_interface_techniques::crtp::exceptions_map {

class RoadAdapter : public IRoad<RoadAdapter> {
 public:
  explicit RoadAdapter(gw::cpp_interface_techniques::exceptions_map::Road& road) noexcept : road_{road} {}

  auto GetLane(LaneId identifier) noexcept -> std::optional<LaneAdapter> {
    try {
      return LaneAdapter{road_.get().GetLane(*identifier)};
    } catch (...) {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetLane(LaneId identifier) const noexcept -> std::optional<const LaneAdapter> {
    try {
      return LaneAdapter{road_.get().GetLane(*identifier)};
    } catch (...) {
      return std::nullopt;
    }
  }

  auto AddLaneLeft() noexcept -> LaneAdapter { return LaneAdapter{road_.get().AddLaneLeft()}; }

  auto AddLaneRight() noexcept -> LaneAdapter { return LaneAdapter{road_.get().AddLaneRight()}; }

  auto GetNextRoad() noexcept -> std::optional<RoadAdapter> {
    try {
      return RoadAdapter{road_.get().GetNextRoad()};
    } catch (...) {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetNextRoad() const noexcept -> std::optional<const RoadAdapter> {
    try {
      return RoadAdapter{road_.get().GetNextRoad()};
    } catch (...) {
      return std::nullopt;
    }
  }

  auto GetPreviousRoad() noexcept -> std::optional<RoadAdapter> {
    try {
      return RoadAdapter{road_.get().GetPreviousRoad()};
    } catch (...) {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> std::optional<const RoadAdapter> {
    try {
      return RoadAdapter{road_.get().GetPreviousRoad()};
    } catch (...) {
      return std::nullopt;
    }
  }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::exceptions_map::Road> road_;
};

}  // namespace gw::cpp_interface_techniques::crtp::exceptions_map
