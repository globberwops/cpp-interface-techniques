// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <functional>  // for std::reference_wrapper
#include <memory>      // for std::unique_ptr

#include "inheritance/interfaces/i_lane.hpp"
#include "optional_map/lane.hpp"

namespace gw::cpp_interface_techniques::inheritance::optional_map {

class LaneAdapter : public ILane {
 public:
  explicit LaneAdapter(gw::cpp_interface_techniques::optional_map::Lane& lane) noexcept : lane_{lane} {}

  ~LaneAdapter() override = default;

  [[nodiscard]] auto GetLength() const noexcept -> double override { return lane_.get().GetLength(); }

  void SetLength(double length) noexcept override { lane_.get().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double override { return lane_.get().GetWidth(); }

  void SetWidth(double width) noexcept override { lane_.get().SetWidth(width); }

  auto GetLeftLane() noexcept -> std::unique_ptr<ILane> override {
    auto lane = lane_.get().GetLeftLane();
    if (lane) {
      return std::make_unique<LaneAdapter>(*lane);
    }
    return nullptr;
  }

  [[nodiscard]] auto GetLeftLane() const noexcept -> std::unique_ptr<const ILane> override {
    auto lane = lane_.get().GetLeftLane();
    if (lane) {
      return std::make_unique<const LaneAdapter>(*lane);
    }
    return nullptr;
  }

  auto GetRightLane() noexcept -> std::unique_ptr<ILane> override {
    auto lane = lane_.get().GetRightLane();
    if (lane) {
      return std::make_unique<LaneAdapter>(*lane);
    }
    return nullptr;
  }

  [[nodiscard]] auto GetRightLane() const noexcept -> std::unique_ptr<const ILane> override {
    auto lane = lane_.get().GetRightLane();
    if (lane) {
      return std::make_unique<const LaneAdapter>(*lane);
    }
    return nullptr;
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
  std::reference_wrapper<gw::cpp_interface_techniques::optional_map::Lane> lane_;
};

}  // namespace gw::cpp_interface_techniques::inheritance::optional_map
