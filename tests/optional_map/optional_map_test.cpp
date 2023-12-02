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
  auto road = GetMap().GetRoad(0U);
  ASSERT_TRUE(road);
  ASSERT_EQ(road->get().GetNextRoad()->get(), GetMap().GetRoad(1U)->get());

  road = GetMap().GetRoad(1U);
  ASSERT_TRUE(road);
  ASSERT_EQ(road->get().GetNextRoad()->get(), GetMap().GetRoad(2U)->get());
  ASSERT_EQ(road->get().GetPreviousRoad()->get(), GetMap().GetRoad(0U)->get());

  road = GetMap().GetRoad(2U);
  ASSERT_TRUE(road);
  ASSERT_EQ(road->get().GetPreviousRoad()->get(), GetMap().GetRoad(1U)->get());

  ASSERT_FALSE(GetMap().GetRoad(3U));
}

TEST_F(OptionalMapTest, LaneNeighbors) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = GetMap().GetRoad(i);
    ASSERT_TRUE(road);

    auto lane = road->get().GetLane(0U);
    ASSERT_TRUE(lane);
    ASSERT_EQ(lane->get().GetRightLane()->get(), road->get().GetLane(1U)->get());

    lane = road->get().GetLane(1U);
    ASSERT_TRUE(lane);
    ASSERT_EQ(lane->get().GetRightLane()->get(), road->get().GetLane(2U)->get());
    ASSERT_EQ(lane->get().GetLeftLane()->get(), road->get().GetLane(0U)->get());

    lane = road->get().GetLane(2U);
    ASSERT_TRUE(lane);
    ASSERT_EQ(lane->get().GetLeftLane()->get(), road->get().GetLane(1U)->get());
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
