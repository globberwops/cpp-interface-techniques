// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <gw/crtp.hpp>  // for gw::Crtp

namespace gw::cpp_interface_techniques::crtp {

template <typename Derived>
class ILane : private gw::Crtp<ILane, Derived> {
 public:
  [[nodiscard]] auto GetLength() const noexcept -> double { return this->Self().GetLength(); }

  void SetLength(double length) noexcept { this->Self().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double { return this->Self().GetWidth(); }

  void SetWidth(double width) noexcept { this->Self().SetWidth(width); }

  auto GetLeftLane() noexcept -> Derived& { return this->Self().GetLeftLane(); }

  [[nodiscard]] auto GetLeftLane() const noexcept -> const Derived& { return this->Self().GetLeftLane(); }

  auto GetRightLane() noexcept -> Derived& { return this->Self().GetRightLane(); }

  [[nodiscard]] auto GetRightLane() const noexcept -> const Derived& { return this->Self().GetRightLane(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
