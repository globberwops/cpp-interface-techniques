#pragma once

#include <functional>  // for std::reference_wrapper
#include <optional>    // for std::optional

namespace optional_map {

class Lane {
 public:
  [[nodiscard]] auto GetLength() const noexcept -> double { return length_; }

  void SetLength(double length) noexcept { length_ = length; }

  [[nodiscard]] auto GetWidth() const noexcept -> double { return width_; }

  void SetWidth(double width) noexcept { width_ = width; }

  [[nodiscard]] auto GetLeftLane() noexcept -> std::optional<std::reference_wrapper<Lane>> { return left_lane_; }

  [[nodiscard]] auto GetLeftLane() const noexcept -> std::optional<std::reference_wrapper<const Lane>> {
    return left_lane_;
  }

  [[nodiscard]] auto GetRightLane() noexcept -> std::optional<std::reference_wrapper<Lane>> { return right_lane_; }

  [[nodiscard]] auto GetRightLane() const noexcept -> std::optional<std::reference_wrapper<const Lane>> {
    return right_lane_;
  }

  auto operator==(const Lane& other) const noexcept -> bool { return &other == this; }

  auto operator!=(const Lane& other) const noexcept -> bool { return &other != this; }

 private:
  friend class Road;

  void SetLeftLane(std::optional<std::reference_wrapper<Lane>> left_lane) noexcept { left_lane_ = left_lane; }

  void SetRightLane(std::optional<std::reference_wrapper<Lane>> right_lane) noexcept { right_lane_ = right_lane; }

  volatile double length_{};
  volatile double width_{};

  std::optional<std::reference_wrapper<Lane>> left_lane_{};
  std::optional<std::reference_wrapper<Lane>> right_lane_{};
};

}  // namespace optional_map
