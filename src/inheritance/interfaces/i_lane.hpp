// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <memory>  // for std::unique_ptr

namespace gw::cpp_interface_techniques::inheritance {

class ILane {
 public:
  virtual ~ILane() = default;

  [[nodiscard]] virtual auto GetLength() const noexcept -> double = 0;

  virtual void SetLength(double length) noexcept = 0;

  [[nodiscard]] virtual auto GetWidth() const noexcept -> double = 0;

  virtual void SetWidth(double width) noexcept = 0;

  virtual auto GetLeftLane() noexcept -> std::unique_ptr<ILane> = 0;

  [[nodiscard]] virtual auto GetLeftLane() const noexcept -> std::unique_ptr<const ILane> = 0;

  virtual auto GetRightLane() noexcept -> std::unique_ptr<ILane> = 0;

  [[nodiscard]] virtual auto GetRightLane() const noexcept -> std::unique_ptr<const ILane> = 0;

  virtual auto operator==(const ILane& other) const noexcept -> bool = 0;
  virtual auto operator!=(const ILane& other) const noexcept -> bool = 0;
};

inline auto operator==(const std::unique_ptr<ILane>& lhs, const std::unique_ptr<ILane>& rhs) noexcept -> bool {
  return *lhs == *rhs;
}

inline auto operator!=(const std::unique_ptr<ILane>& lhs, const std::unique_ptr<ILane>& rhs) noexcept -> bool {
  return !(*lhs == *rhs);
}

}  // namespace gw::cpp_interface_techniques::inheritance
