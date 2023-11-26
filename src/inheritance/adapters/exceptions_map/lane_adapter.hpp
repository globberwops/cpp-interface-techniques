// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <memory>      // for std::unique_ptr

#include "exceptions_map/lane.hpp"
#include "inheritance/interfaces/i_lane.hpp"

namespace gw::cpp_interface_techniques::inheritance::exceptions_map {

class LaneAdapter : public ILane {
 public:
  explicit LaneAdapter(gw::cpp_interface_techniques::exceptions_map::Lane& lane) noexcept : lane_{lane} {}

  ~LaneAdapter() override = default;

  [[nodiscard]] auto GetLength() const noexcept -> double override { return lane_.get().GetLength(); }

  void SetLength(double length) noexcept override { lane_.get().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double override { return lane_.get().GetWidth(); }

  void SetWidth(double width) noexcept override { lane_.get().SetWidth(width); }

  auto GetLeftLane() noexcept -> std::unique_ptr<ILane> override {
    try {
      return std::make_unique<LaneAdapter>(lane_.get().GetLeftLane());
    } catch (...) {
      return nullptr;
    }
  }

  [[nodiscard]] auto GetLeftLane() const noexcept -> std::unique_ptr<const ILane> override {
    try {
      return std::make_unique<const LaneAdapter>(lane_.get().GetLeftLane());
    } catch (...) {
      return nullptr;
    }
  }

  auto GetRightLane() noexcept -> std::unique_ptr<ILane> override {
    try {
      return std::make_unique<LaneAdapter>(lane_.get().GetRightLane());
    } catch (...) {
      return nullptr;
    }
  }

  [[nodiscard]] auto GetRightLane() const noexcept -> std::unique_ptr<const ILane> override {
    try {
      return std::make_unique<const LaneAdapter>(lane_.get().GetRightLane());
    } catch (...) {
      return nullptr;
    }
  }

  auto operator==(const ILane& other) const noexcept -> bool override {
    const auto* other_cast = dynamic_cast<const LaneAdapter*>(&other);
    if (other_cast == nullptr) {
      return false;
    }

    return &lane_.get() == &other_cast->lane_.get();
  }

  auto operator!=(const ILane& rhs) const noexcept -> bool override { return !(*this == rhs); }

 private:
  std::reference_wrapper<gw::cpp_interface_techniques::exceptions_map::Lane> lane_;
};

}  // namespace gw::cpp_interface_techniques::inheritance::exceptions_map
