#include <type_traits>

#include "gw/strong_type.hpp"

using StrongTypeStatic = gw::StrongType<int, struct StrongTypeStaticTag>;

static_assert(std::is_nothrow_default_constructible_v<StrongTypeStatic>);
static_assert(std::is_nothrow_copy_constructible_v<StrongTypeStatic>);
static_assert(std::is_nothrow_move_constructible_v<StrongTypeStatic>);
static_assert(std::is_nothrow_copy_assignable_v<StrongTypeStatic>);
static_assert(std::is_nothrow_move_assignable_v<StrongTypeStatic>);
static_assert(std::is_nothrow_destructible_v<StrongTypeStatic>);
static_assert(std::is_nothrow_swappable_v<StrongTypeStatic>);

static_assert(std::is_nothrow_constructible_v<StrongTypeStatic, int>);
static_assert(std::is_nothrow_constructible_v<StrongTypeStatic, int&>);
static_assert(std::is_nothrow_constructible_v<StrongTypeStatic, int&&>);
static_assert(std::is_nothrow_constructible_v<StrongTypeStatic, const int>);
static_assert(std::is_nothrow_constructible_v<StrongTypeStatic, const int&>);
static_assert(std::is_nothrow_constructible_v<StrongTypeStatic, const int&&>);

consteval auto OperatorParensIsNoexcept() noexcept -> bool {
  auto strong_type = StrongTypeStatic{};
  return noexcept(*strong_type);
}
static_assert(OperatorParensIsNoexcept());

consteval auto ConstOperatorParensIsNoexcept() noexcept -> bool {
  const auto kStrongType = StrongTypeStatic{};
  return noexcept(*kStrongType);
}
static_assert(ConstOperatorParensIsNoexcept());

static_assert(*StrongTypeStatic{} == 0);

static_assert(StrongTypeStatic{} == StrongTypeStatic{});
static_assert(StrongTypeStatic{} != StrongTypeStatic{1});
static_assert(StrongTypeStatic{} <= StrongTypeStatic{1});
static_assert(StrongTypeStatic{} < StrongTypeStatic{1});
static_assert(StrongTypeStatic{1} >= StrongTypeStatic{});
static_assert(StrongTypeStatic{1} > StrongTypeStatic{});
