// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "crtp/adapters/optional_map/lane_adapter.hpp"
#include "crtp/interfaces/i_road.hpp"
#include "optional_map/road.hpp"

namespace gw::cpp_interface_techniques::crtp::optional_map {

class RoadAdapter : public IRoad<RoadAdapter> {
 public:
  explicit RoadAdapter(gw::cpp_interface_techniques::optional_map::Road& road) noexcept : road_{road} {}

  auto GetLane(LaneId identifier) noexcept -> std::optional<LaneAdapter> {
    auto lane = road_.get().GetLane(*identifier);
    if (lane) {
      return LaneAdapter{*lane};
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetLane(LaneId identifier) const noexcept -> std::optional<const LaneAdapter> {
    auto lane = road_.get().GetLane(*identifier);
    if (lane) {
      return LaneAdapter{*lane};
    }
    return std::nullopt;
  }

  auto AddLaneLeft() noexcept -> LaneAdapter { return LaneAdapter{road_.get().AddLaneLeft()}; }

  auto AddLaneRight() noexcept -> LaneAdapter { return LaneAdapter{road_.get().AddLaneRight()}; }

  auto GetNextRoad() noexcept -> std::optional<RoadAdapter> {
    auto road = road_.get().GetNextRoad();
    if (road) {
      return RoadAdapter{*road};
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetNextRoad() const noexcept -> std::optional<const RoadAdapter> {
    auto road = road_.get().GetNextRoad();
    if (road) {
      return RoadAdapter{*road};
    }
    return std::nullopt;
  }

  auto GetPreviousRoad() noexcept -> std::optional<RoadAdapter> {
    auto road = road_.get().GetPreviousRoad();
    if (road) {
      return RoadAdapter{*road};
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> std::optional<const RoadAdapter> {
    auto road = road_.get().GetPreviousRoad();
    if (road) {
      return RoadAdapter{*road};
    }
    return std::nullopt;
  }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::optional_map::Road> road_;
};

}  // namespace gw::cpp_interface_techniques::crtp::optional_map
