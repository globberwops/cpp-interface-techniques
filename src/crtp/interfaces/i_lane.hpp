// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace gw::cpp_interface_techniques::crtp {

template <typename Derived>
class ILane {
 public:
  [[nodiscard]] auto GetLength() const noexcept -> double { return Self().GetLength(); }

  void SetLength(double length) noexcept { Self().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double { return Self().GetWidth(); }

  void SetWidth(double width) noexcept { Self().SetWidth(width); }

  auto GetLeftLane() noexcept -> Derived& { return Self().GetLeftLane(); }

  [[nodiscard]] auto GetLeftLane() const noexcept -> const Derived& { return Self().GetLeftLane(); }

  auto GetRightLane() noexcept -> Derived& { return Self().GetRightLane(); }

  [[nodiscard]] auto GetRightLane() const noexcept -> const Derived& { return Self().GetRightLane(); }

 private:
  constexpr auto Self() noexcept -> Derived& { return static_cast<Derived&>(*this); }
  constexpr auto Self() const noexcept -> const Derived& { return static_cast<const Derived&>(*this); }
};

}  // namespace gw::cpp_interface_techniques::crtp
