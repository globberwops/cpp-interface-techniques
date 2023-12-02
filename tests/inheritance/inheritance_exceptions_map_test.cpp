// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <exceptions_map/map.hpp>
#include <exceptions_map/road.hpp>

#include "inheritance/adapters/exceptions_map/map_adapter.hpp"
#include "inheritance/interfaces/i_map.hpp"
#include "inheritance/interfaces/i_road.hpp"

using gw::cpp_interface_techniques::exceptions_map::Map;
using gw::cpp_interface_techniques::exceptions_map::MapFactory;
using gw::cpp_interface_techniques::inheritance::IMap;
using gw::cpp_interface_techniques::inheritance::LaneId;
using gw::cpp_interface_techniques::inheritance::RoadId;
using gw::cpp_interface_techniques::inheritance::exceptions_map::MapAdapter;

class InheritanceExceptionsMapTest : public testing::Test {
 protected:
  void SetUp() override { map_ = MapFactory::Create(); }

  auto GetMap() -> IMap& { return map_adapter_; }

 private:
  Map map_{};
  MapAdapter map_adapter_{map_};
};

TEST_F(InheritanceExceptionsMapTest, RoadPredecessorsAndSuccessors) {
  auto road = GetMap().GetRoad(RoadId{0U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetNextRoad(), GetMap().GetRoad(RoadId{1U}));

  road = GetMap().GetRoad(RoadId{1U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetNextRoad(), GetMap().GetRoad(RoadId{2U}));
  ASSERT_EQ(road->GetPreviousRoad(), GetMap().GetRoad(RoadId{0U}));

  road = GetMap().GetRoad(RoadId{2U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetPreviousRoad(), GetMap().GetRoad(RoadId{1U}));
}

TEST_F(InheritanceExceptionsMapTest, LaneNeighbors) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = GetMap().GetRoad(RoadId{i});
    ASSERT_TRUE(road);

    auto lane = road->GetLane(LaneId{0U});
    ASSERT_TRUE(lane);
    ASSERT_EQ(lane->GetRightLane(), road->GetLane(LaneId{1U}));

    lane = road->GetLane(LaneId{1U});
    ASSERT_TRUE(lane);
    ASSERT_EQ(lane->GetRightLane(), road->GetLane(LaneId{2U}));
    ASSERT_EQ(lane->GetLeftLane(), road->GetLane(LaneId{0U}));

    lane = road->GetLane(LaneId{2U});
    ASSERT_TRUE(lane);
    ASSERT_EQ(lane->GetLeftLane(), road->GetLane(LaneId{1U}));
  }
}

TEST_F(InheritanceExceptionsMapTest, LaneLengthAndWidth) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = GetMap().GetRoad(RoadId{i});
    ASSERT_TRUE(road);

    for (auto j = 0U; j <= 2; ++j) {
      auto lane = road->GetLane(LaneId{j});
      ASSERT_TRUE(lane);

      ASSERT_DOUBLE_EQ(lane->GetLength(), MapFactory::kLaneLength);
      ASSERT_DOUBLE_EQ(lane->GetWidth(), MapFactory::kLaneWidth);
    }
  }
}