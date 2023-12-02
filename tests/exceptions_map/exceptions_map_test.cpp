// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <stdexcept>

#include "exceptions_map/lane.hpp"
#include "exceptions_map/map.hpp"
#include "exceptions_map/road.hpp"

using gw::cpp_interface_techniques::exceptions_map::Map;
using gw::cpp_interface_techniques::exceptions_map::MapFactory;

class ExceptionsMapTest : public testing::Test {
 protected:
  void SetUp() override { map_ = MapFactory::Create(); }

  auto GetMap() -> Map& { return map_; }

 private:
  Map map_{};
};

TEST_F(ExceptionsMapTest, RoadPredecessorsAndSuccessors) {
  auto& road = GetMap().GetRoad(0U);
  ASSERT_EQ(road.GetNextRoad(), GetMap().GetRoad(1U));

  road = GetMap().GetRoad(1U);
  ASSERT_EQ(road.GetNextRoad(), GetMap().GetRoad(2U));
  ASSERT_EQ(road.GetPreviousRoad(), GetMap().GetRoad(0U));

  road = GetMap().GetRoad(2U);
  ASSERT_EQ(road.GetPreviousRoad(), GetMap().GetRoad(1U));

  ASSERT_THROW(GetMap().GetRoad(3U), std::out_of_range);
}

TEST_F(ExceptionsMapTest, LaneNeighbors) {
  for (auto i = 0U; i <= 2; ++i) {
    auto& road = GetMap().GetRoad(i);

    auto& lane = road.GetLane(0U);
    ASSERT_EQ(lane.GetRightLane(), road.GetLane(1U));

    lane = road.GetLane(1U);
    ASSERT_EQ(lane.GetRightLane(), road.GetLane(2U));
    ASSERT_EQ(lane.GetLeftLane(), road.GetLane(0U));

    lane = road.GetLane(2U);
    ASSERT_EQ(lane.GetLeftLane(), road.GetLane(1U));
  }
}

TEST_F(ExceptionsMapTest, LaneLengthAndWidth) {
  for (auto i = 0U; i <= 2; ++i) {
    auto& road = GetMap().GetRoad(i);

    for (auto j = 0U; j <= 2; ++j) {
      auto& lane = road.GetLane(j);

      ASSERT_DOUBLE_EQ(lane.GetLength(), MapFactory::kLaneLength);
      ASSERT_DOUBLE_EQ(lane.GetWidth(), MapFactory::kLaneWidth);
    }
  }
}
