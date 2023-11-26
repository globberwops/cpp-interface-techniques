// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <memory>      // for std::unique_ptr

#include "inheritance/adapters/optional_map/road_adapter.hpp"
#include "inheritance/interfaces/i_map.hpp"
#include "optional_map/map.hpp"

namespace gw::cpp_interface_techniques::inheritance::optional_map {

class MapAdapter : public IMap {
 public:
  explicit MapAdapter(gw::cpp_interface_techniques::optional_map::Map& map) noexcept : map_{map} {}

  ~MapAdapter() override = default;

  auto GetRoad(RoadId identifier) noexcept -> std::unique_ptr<IRoad> override {
    auto road = map_.get().GetRoad(*identifier);
    if (road) {
      return std::make_unique<RoadAdapter>(*road);
    }
    return nullptr;
  }

  [[nodiscard]] auto GetRoad(RoadId identifier) const noexcept -> std::unique_ptr<const IRoad> override {
    auto road = map_.get().GetRoad(*identifier);
    if (road) {
      return std::make_unique<const RoadAdapter>(*road);
    }
    return nullptr;
  }

  auto AddRoadFront() noexcept -> std::unique_ptr<IRoad> override {
    return std::make_unique<RoadAdapter>(map_.get().AddRoadFront());
  }

  auto AddRoadBack() noexcept -> std::unique_ptr<IRoad> override {
    return std::make_unique<RoadAdapter>(map_.get().AddRoadBack());
  }

  auto operator==(const IMap& other) const noexcept -> bool override {
    const auto* other_cast = dynamic_cast<const MapAdapter*>(&other);
    if (other_cast == nullptr) {
      return false;
    }

    return &map_.get() == &other_cast->map_.get();
  }

  auto operator!=(const IMap& rhs) const noexcept -> bool override { return !(*this == rhs); }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::optional_map::Map> map_;
};

}  // namespace gw::cpp_interface_techniques::inheritance::optional_map
