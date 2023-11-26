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
  ASSERT_EQ(GetMap().GetRoad(0U).get().GetNextRoad().get(), GetMap().GetRoad(1U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetNextRoad().get(), GetMap().GetRoad(2U).get());
  ASSERT_EQ(GetMap().GetRoad(2U).get().GetPreviousRoad().get(), GetMap().GetRoad(1U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetPreviousRoad().get(), GetMap().GetRoad(0U).get());

  ASSERT_THROW(GetMap().GetRoad(3U), std::out_of_range);
}

TEST_F(ExceptionsMapTest, LaneNeighbors) {
  for (auto i = 0U; i <= 2; ++i) {
    auto& road = GetMap().GetRoad(i).get();

    ASSERT_EQ(road.GetLane(0U).get().GetRightLane().get(), road.GetLane(1U).get());
    ASSERT_EQ(road.GetLane(1U).get().GetRightLane().get(), road.GetLane(2U).get());
    ASSERT_EQ(road.GetLane(2U).get().GetLeftLane().get(), road.GetLane(1U).get());
    ASSERT_EQ(road.GetLane(1U).get().GetLeftLane().get(), road.GetLane(0U).get());
  }
}

TEST_F(ExceptionsMapTest, LaneLengthAndWidth) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = GetMap().GetRoad(i);

    for (auto j = 0U; j <= 2; ++j) {
      auto lane = road.get().GetLane(j);

      ASSERT_DOUBLE_EQ(lane.get().GetLength(), MapFactory::kLaneLength);
      ASSERT_DOUBLE_EQ(lane.get().GetWidth(), MapFactory::kLaneWidth);
    }
  }
}
