// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include "crtp/adapters/exceptions_map/lane_adapter.hpp"
#include "crtp/adapters/exceptions_map/map_adapter.hpp"
#include "crtp/adapters/exceptions_map/road_adapter.hpp"
#include "crtp/interfaces/i_map.hpp"
#include "crtp/interfaces/i_road.hpp"
#include "exceptions_map/map.hpp"

TEST(CrtpTest, MapAdapter) {
  using gw::cpp_interface_techniques::crtp::LaneId;
  using gw::cpp_interface_techniques::crtp::RoadId;

  auto map = gw::cpp_interface_techniques::exceptions_map::Map{};
  auto map_adapter = gw::cpp_interface_techniques::crtp::exceptions_map::MapAdapter{map};

  auto road_adapter = map_adapter.AddRoadBack();
  auto lane_adapter1 = road_adapter.AddLaneRight();
  lane_adapter1.SetLength(100.0);

  auto lane_adapter2 = road_adapter.AddLaneRight();
  lane_adapter2.SetLength(200.0);

  const auto& const_map_adapter = map_adapter;
  const auto kRoadAdapter = const_map_adapter.GetRoad(RoadId{});
  ASSERT_TRUE(kRoadAdapter);

  const auto kLaneAdapter1 = kRoadAdapter->GetLane(LaneId{});
  ASSERT_TRUE(kLaneAdapter1);
  ASSERT_DOUBLE_EQ(kLaneAdapter1->GetLength(), 100.0);

  const auto kLaneAdapter2 = kLaneAdapter1->GetRightLane();
  ASSERT_TRUE(kLaneAdapter2);
  ASSERT_DOUBLE_EQ(kLaneAdapter2->GetLength(), 200.0);

  const auto kLaneAdapter3 = kLaneAdapter2->GetRightLane();
  ASSERT_FALSE(kLaneAdapter3);
}
