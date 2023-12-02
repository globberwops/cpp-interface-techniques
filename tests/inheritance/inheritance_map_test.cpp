// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <exceptions_map/map.hpp>
#include <optional_map/map.hpp>

#include "inheritance/adapters/exceptions_map/map_adapter.hpp"
#include "inheritance/adapters/optional_map/map_adapter.hpp"
#include "inheritance/interfaces/i_map.hpp"
#include "inheritance/interfaces/i_road.hpp"

using gw::cpp_interface_techniques::inheritance::IMap;
using gw::cpp_interface_techniques::inheritance::LaneId;
using gw::cpp_interface_techniques::inheritance::RoadId;

template <typename Map, typename MapFactory, typename MapAdapter>
struct TestMap {
  using MapType = Map;
  using MapFactoryType = MapFactory;
  using MapAdapterType = MapAdapter;

  Map map{MapFactory::Create()};
  MapAdapter map_adapter{map};
};

template <typename TestMap>
class InheritanceMapTest : public testing::Test {
 protected:
  auto GetMap() -> IMap& { return test_map_.map_adapter; }

 private:
  TestMap test_map_{};
};

TYPED_TEST_SUITE_P(InheritanceMapTest);

TYPED_TEST_P(InheritanceMapTest, RoadPredecessorsAndSuccessors) {
  auto road = this->GetMap().GetRoad(RoadId{0U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetNextRoad(), this->GetMap().GetRoad(RoadId{1U}));

  road = this->GetMap().GetRoad(RoadId{1U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetNextRoad(), this->GetMap().GetRoad(RoadId{2U}));
  ASSERT_EQ(road->GetPreviousRoad(), this->GetMap().GetRoad(RoadId{0U}));

  road = this->GetMap().GetRoad(RoadId{2U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetPreviousRoad(), this->GetMap().GetRoad(RoadId{1U}));
}

TYPED_TEST_P(InheritanceMapTest, LaneNeighbors) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = this->GetMap().GetRoad(RoadId{i});
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

TYPED_TEST_P(InheritanceMapTest, LaneLengthAndWidth) {
  for (auto i = 0U; i <= 2; ++i) {
    auto road = this->GetMap().GetRoad(RoadId{i});
    ASSERT_TRUE(road);

    for (auto j = 0U; j <= 2; ++j) {
      auto lane = road->GetLane(LaneId{j});
      ASSERT_TRUE(lane);

      ASSERT_DOUBLE_EQ(lane->GetLength(), TypeParam::MapFactoryType::kLaneLength);
      ASSERT_DOUBLE_EQ(lane->GetWidth(), TypeParam::MapFactoryType::kLaneWidth);
    }
  }
}

REGISTER_TYPED_TEST_SUITE_P(InheritanceMapTest, RoadPredecessorsAndSuccessors, LaneNeighbors, LaneLengthAndWidth);

using ExceptionsTestMap =
    TestMap<gw::cpp_interface_techniques::exceptions_map::Map, gw::cpp_interface_techniques::exceptions_map::MapFactory,
            gw::cpp_interface_techniques::inheritance::exceptions_map::MapAdapter>;

using OptionalTestMap =
    TestMap<gw::cpp_interface_techniques::optional_map::Map, gw::cpp_interface_techniques::optional_map::MapFactory,
            gw::cpp_interface_techniques::inheritance::optional_map::MapAdapter>;

using TestMapTypes = ::testing::Types<ExceptionsTestMap, OptionalTestMap>;
INSTANTIATE_TYPED_TEST_SUITE_P(Inheritance, InheritanceMapTest, TestMapTypes);
