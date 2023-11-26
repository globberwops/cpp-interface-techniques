// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <gw/crtp.hpp>  // for gw::Crtp

namespace gw::cpp_interface_techniques::crtp {

template <typename Derived>
class ILane : public gw::crtp<ILane, Derived> {
 public:
  [[nodiscard]] auto GetLength() const noexcept -> double { return this->self().GetLength(); }

  void SetLength(double length) noexcept { this->self().SetLength(length); }

  [[nodiscard]] auto GetWidth() const noexcept -> double { return this->self().GetWidth(); }

  void SetWidth(double width) noexcept { this->self().SetWidth(width); }

  auto GetLeftLane() noexcept -> Derived& { return this->self().GetLeftLane(); }

  [[nodiscard]] auto GetLeftLane() const noexcept -> const Derived& { return this->self().GetLeftLane(); }

  auto GetRightLane() noexcept -> Derived& { return this->self().GetRightLane(); }

  [[nodiscard]] auto GetRightLane() const noexcept -> const Derived& { return this->self().GetRightLane(); }
};

}  // namespace gw::cpp_interface_techniques::crtp
