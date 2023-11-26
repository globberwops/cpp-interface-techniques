// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <functional>

#include "optional_map/lane.hpp"
#include "optional_map/map.hpp"
#include "optional_map/road.hpp"

using gw::cpp_interface_techniques::optional_map::Map;
using gw::cpp_interface_techniques::optional_map::MapFactory;

class OptionalMapTest : public testing::Test {
 protected:
  void SetUp() override { map_ = MapFactory::Create(); }

  auto GetMap() -> Map& { return map_; }

 private:
  Map map_{};
};

TEST_F(OptionalMapTest, RoadPredecessorsAndSuccessors) {
  ASSERT_EQ(GetMap().GetRoad(0U)->get().GetNextRoad()->get(), GetMap().GetRoad(1U)->get());
  ASSERT_EQ(GetMap().GetRoad(1U)->get().GetNextRoad()->get(), GetMap().GetRoad(2U)->get());
  ASSERT_EQ(GetMap().GetRoad(2U)->get().GetPreviousRoad()->get(), GetMap().GetRoad(1U)->get());
  ASSERT_EQ(GetMap().GetRoad(1U)->get().GetPreviousRoad()->get(), GetMap().GetRoad(0U)->get());
}

TEST_F(OptionalMapTest, LaneNeighbors) {
  for (auto i = 0U; i <= 2; ++i) {
    auto& road = GetMap().GetRoad(i)->get();

    ASSERT_EQ(road.GetLane(0U)->get().GetRightLane()->get(), road.GetLane(1U)->get());
    ASSERT_EQ(road.GetLane(1U)->get().GetRightLane()->get(), road.GetLane(2U)->get());
    ASSERT_EQ(road.GetLane(2U)->get().GetLeftLane()->get(), road.GetLane(1U)->get());
    ASSERT_EQ(road.GetLane(1U)->get().GetLeftLane()->get(), road.GetLane(0U)->get());
  }
}

TEST_F(OptionalMapTest, LaneLengthAndWidth) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = GetMap().GetRoad(i);
    ASSERT_TRUE(road);

    for (auto j = 0U; j <= 2; ++j) {
      auto lane = road->get().GetLane(j);
      ASSERT_TRUE(lane);

      ASSERT_DOUBLE_EQ(lane->get().GetLength(), MapFactory::kLaneLength);
      ASSERT_DOUBLE_EQ(lane->get().GetWidth(), MapFactory::kLaneWidth);
    }
  }
}
