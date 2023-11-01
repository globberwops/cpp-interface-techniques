// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <type_traits>
#include <utility>

namespace gw {

template <typename T, typename Tag>
struct StrongType {
  constexpr StrongType() noexcept(std::is_nothrow_default_constructible_v<T>)
    requires std::is_default_constructible_v<T>
  = default;

  constexpr explicit StrongType(const T& value) noexcept(std::is_nothrow_copy_constructible_v<T>)
    requires std::is_copy_constructible_v<T>
      : value_{value} {}

  constexpr explicit StrongType(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>)
    requires std::is_move_constructible_v<T>
      : value_{std::move(value)} {}

  constexpr auto operator->() const noexcept -> const T* { return &value_; }
  constexpr auto operator->() noexcept -> T* { return &value_; }
  constexpr auto operator*() const& noexcept -> const T& { return value_; }
  constexpr auto operator*() & noexcept -> T& { return value_; }
  constexpr auto operator*() const&& noexcept -> const T&& { return std::move(value_); }
  constexpr auto operator*() && noexcept -> T&& { return std::move(value_); }

  constexpr auto operator<=>(const StrongType&) const noexcept = default;

 private:
  T value_{};
};

}  // namespace gw
