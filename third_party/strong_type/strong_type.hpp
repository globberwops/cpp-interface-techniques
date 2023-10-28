// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#pragma once

#if __cplusplus > 201703L && __cpp_impl_three_way_comparison >= 201907L
#include <compare>  // for operator<=>
#endif

#include <utility>  // for std::move

namespace gw {

template <typename T, typename Tag>
class StrongType {
 public:
  constexpr StrongType() noexcept = default;
  constexpr explicit StrongType(const T& value) noexcept : value_{value} {}
  constexpr explicit StrongType(T&& value) noexcept : value_{std::move(value)} {}

#if __cplusplus > 201703L && __cpp_impl_three_way_comparison >= 201907L
  constexpr auto operator<=>(const StrongType&) const noexcept = default;
#else
  constexpr auto operator==(const StrongType& other) const noexcept -> bool { return value_ == other.value_; }
  constexpr auto operator!=(const StrongType& other) const noexcept -> bool { return value_ != other.value_; }
  constexpr auto operator<(const StrongType& other) const noexcept -> bool { return value_ < other.value_; }
  constexpr auto operator>(const StrongType& other) const noexcept -> bool { return value_ > other.value_; }
  constexpr auto operator<=(const StrongType& other) const noexcept -> bool { return value_ <= other.value_; }
  constexpr auto operator>=(const StrongType& other) const noexcept -> bool { return value_ >= other.value_; }
#endif

 private:
  T value_{};
};

}  // namespace gw
