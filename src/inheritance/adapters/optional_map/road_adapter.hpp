// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <memory>      // for std::unique_ptr

#include "inheritance/adapters/optional_map/lane_adapter.hpp"
#include "inheritance/interfaces/i_road.hpp"
#include "optional_map/road.hpp"

namespace gw::cpp_interface_techniques::inheritance::optional_map {

class RoadAdapter : public IRoad {
 public:
  explicit RoadAdapter(gw::cpp_interface_techniques::optional_map::Road& road) noexcept : road_{road} {}

  ~RoadAdapter() override = default;

  auto GetLane(LaneId identifier) noexcept -> std::unique_ptr<ILane> override {
    auto lane = road_.get().GetLane(*identifier);
    if (lane) {
      return std::make_unique<LaneAdapter>(*lane);
    }
    return nullptr;
  }

  [[nodiscard]] auto GetLane(LaneId identifier) const noexcept -> std::unique_ptr<const ILane> override {
    auto lane = road_.get().GetLane(*identifier);
    if (lane) {
      return std::make_unique<const LaneAdapter>(*lane);
    }
    return nullptr;
  }

  auto AddLaneLeft() noexcept -> std::unique_ptr<ILane> override {
    return std::make_unique<LaneAdapter>(road_.get().AddLaneLeft());
  }

  auto AddLaneRight() noexcept -> std::unique_ptr<ILane> override {
    return std::make_unique<LaneAdapter>(road_.get().AddLaneRight());
  }

  auto GetNextRoad() noexcept -> std::unique_ptr<IRoad> override {
    auto road = road_.get().GetNextRoad();
    if (road) {
      return std::make_unique<RoadAdapter>(*road);
    }
    return nullptr;
  }

  [[nodiscard]] auto GetNextRoad() const noexcept -> std::unique_ptr<const IRoad> override {
    auto road = road_.get().GetNextRoad();
    if (road) {
      return std::make_unique<const RoadAdapter>(*road);
    }
    return nullptr;
  }

  auto GetPreviousRoad() noexcept -> std::unique_ptr<IRoad> override {
    auto road = road_.get().GetPreviousRoad();
    if (road) {
      return std::make_unique<RoadAdapter>(*road);
    }
    return nullptr;
  }

  [[nodiscard]] auto GetPreviousRoad() const noexcept -> std::unique_ptr<const IRoad> override {
    auto road = road_.get().GetPreviousRoad();
    if (road) {
      return std::make_unique<const RoadAdapter>(*road);
    }
    return nullptr;
  }

  auto operator==(const IRoad& other) const noexcept -> bool override {
    const auto* other_cast = dynamic_cast<const RoadAdapter*>(&other);
    if (other_cast == nullptr) {
      return false;
    }

    return &road_.get() == &other_cast->road_.get();
  }

  auto operator!=(const IRoad& rhs) const noexcept -> bool override { return !(*this == rhs); }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::optional_map::Road> road_;
};

}  // namespace gw::cpp_interface_techniques::inheritance::optional_map
