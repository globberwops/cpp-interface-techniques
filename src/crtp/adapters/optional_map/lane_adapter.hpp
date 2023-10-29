// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "crtp/interfaces/i_lane.hpp"
#include "optional_map/lane.hpp"

namespace gw::cpp_interface_techniques::crtp::optional_map {

class LaneAdapter : public ILane<LaneAdapter> {
 public:
  explicit LaneAdapter(gw::cpp_interface_techniques::optional_map::Lane& lane) noexcept : lane_{lane} {}

  [[nodiscard]] auto GetLength() const noexcept -> double { return lane_.get().GetLength(); }

  void SetLength(double length) noexcept { lane_.get().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double { return lane_.get().GetWidth(); }

  void SetWidth(double width) noexcept { lane_.get().SetWidth(width); }

  auto GetLeftLane() noexcept -> std::optional<LaneAdapter> {
    auto lane = lane_.get().GetLeftLane();
    if (lane) {
      return LaneAdapter{*lane};
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetLeftLane() const noexcept -> std::optional<const LaneAdapter> {
    auto lane = lane_.get().GetLeftLane();
    if (lane) {
      return LaneAdapter{*lane};
    }
    return std::nullopt;
  }

  auto GetRightLane() noexcept -> std::optional<LaneAdapter> {
    auto lane = lane_.get().GetRightLane();
    if (lane) {
      return LaneAdapter{*lane};
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetRightLane() const noexcept -> std::optional<const LaneAdapter> {
    auto lane = lane_.get().GetRightLane();
    if (lane) {
      return LaneAdapter{*lane};
    }
    return std::nullopt;
  }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::optional_map::Lane> lane_;
};

}  // namespace gw::cpp_interface_techniques::crtp::optional_map
