// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

#include "crtp/interfaces/i_lane.hpp"
#include "exceptions_map/lane.hpp"

namespace gw::cpp_interface_techniques::crtp::exceptions_map {

class LaneAdapter : public ILane<LaneAdapter> {
 public:
  explicit LaneAdapter(gw::cpp_interface_techniques::exceptions_map::Lane& lane) noexcept : lane_{lane} {}

  [[nodiscard]] auto GetLength() const noexcept -> double { return lane_.get().GetLength(); }

  void SetLength(double length) noexcept { lane_.get().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double { return lane_.get().GetWidth(); }

  void SetWidth(double width) noexcept { lane_.get().SetWidth(width); }

  auto GetLeftLane() noexcept -> std::optional<LaneAdapter> {
    try {
      return LaneAdapter{lane_.get().GetLeftLane()};
    } catch (...) {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetLeftLane() const noexcept -> std::optional<const LaneAdapter> {
    try {
      return LaneAdapter{lane_.get().GetLeftLane()};
    } catch (...) {
      return std::nullopt;
    }
  }

  auto GetRightLane() noexcept -> std::optional<LaneAdapter> {
    try {
      return LaneAdapter{lane_.get().GetRightLane()};
    } catch (...) {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetRightLane() const noexcept -> std::optional<const LaneAdapter> {
    try {
      return LaneAdapter{lane_.get().GetRightLane()};
    } catch (...) {
      return std::nullopt;
    }
  }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::exceptions_map::Lane> lane_;
};

}  // namespace gw::cpp_interface_techniques::crtp::exceptions_map
