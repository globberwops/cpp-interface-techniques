// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional
#include <stdexcept>   // for std::runtime_error

namespace gw::cpp_interface_techniques::exceptions_map {

class Lane {
 public:
  [[nodiscard]] auto GetLength() const -> double { return length_; }

  void SetLength(double length) { length_ = length; }

  [[nodiscard]] auto GetWidth() const -> double { return width_; }

  void SetWidth(double width) { width_ = width; }

  [[nodiscard]] auto GetLeftLane() -> Lane& {
    return left_lane_.has_value() ? left_lane_.value().get() : throw std::runtime_error("No left lane");
  }

  [[nodiscard]] auto GetLeftLane() const -> const Lane& {
    return left_lane_.has_value() ? left_lane_.value().get() : throw std::runtime_error("No left lane");
  }

  [[nodiscard]] auto GetRightLane() -> Lane& {
    return right_lane_.has_value() ? right_lane_.value().get() : throw std::runtime_error("No right lane");
  }

  [[nodiscard]] auto GetRightLane() const -> const Lane& {
    return right_lane_.has_value() ? right_lane_.value().get() : throw std::runtime_error("No right lane");
  }

  auto operator==(const Lane& other) const noexcept -> bool { return &other == this; }

  auto operator!=(const Lane& other) const noexcept -> bool { return &other != this; }

 private:
  friend class Road;

  void SetLeftLane(Lane& left_lane) { left_lane_ = left_lane; }

  void SetRightLane(Lane& right_lane) { right_lane_ = right_lane; }

  volatile double length_{};
  volatile double width_{};

  std::optional<std::reference_wrapper<Lane>> left_lane_{};
  std::optional<std::reference_wrapper<Lane>> right_lane_{};
};

}  // namespace gw::cpp_interface_techniques::exceptions_map
