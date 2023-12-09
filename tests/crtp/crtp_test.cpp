// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <exceptions_map/map.hpp>
#include <optional_map/map.hpp>

#include "crtp/adapters/exceptions_map/map_adapter.hpp"
#include "crtp/adapters/optional_map/map_adapter.hpp"
#include "crtp/interfaces/i_map.hpp"
#include "crtp/interfaces/i_road.hpp"

using gw::cpp_interface_techniques::crtp::IMap;
using gw::cpp_interface_techniques::crtp::LaneId;
using gw::cpp_interface_techniques::crtp::RoadId;

template <typename Map, typename MapFactory, typename MapAdapter>
struct MapTypeParam {
  using MapType = Map;
  using MapFactoryType = MapFactory;
  using MapAdapterType = MapAdapter;

  Map map{MapFactory::Create()};
  MapAdapter map_adapter{map};
};

template <typename T>
class CrtpTest : public testing::Test {
 protected:
  auto GetMap() -> IMap<typename T::MapAdapterType>& { return map_type_param_.map_adapter; }

 private:
  T map_type_param_{};
};

using ExceptionsMapTypeParam = MapTypeParam<gw::cpp_interface_techniques::exceptions_map::Map,
                                            gw::cpp_interface_techniques::exceptions_map::MapFactory,
                                            gw::cpp_interface_techniques::crtp::exceptions_map::MapAdapter>;

using OptionalMapTypeParam = MapTypeParam<gw::cpp_interface_techniques::optional_map::Map,
                                          gw::cpp_interface_techniques::optional_map::MapFactory,
                                          gw::cpp_interface_techniques::crtp::optional_map::MapAdapter>;

using MapTypeParams = ::testing::Types<ExceptionsMapTypeParam, OptionalMapTypeParam>;

TYPED_TEST_SUITE(CrtpTest, MapTypeParams);

TYPED_TEST(CrtpTest, RoadPredecessorsAndSuccessors) {
  decltype(auto) map = this->GetMap();

  auto road = map.GetRoad(RoadId{0U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetNextRoad(), map.GetRoad(RoadId{1U}));

  road = map.GetRoad(RoadId{1U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetNextRoad(), map.GetRoad(RoadId{2U}));
  ASSERT_EQ(road->GetPreviousRoad(), map.GetRoad(RoadId{0U}));

  road = map.GetRoad(RoadId{2U});
  ASSERT_TRUE(road);
  ASSERT_EQ(road->GetPreviousRoad(), map.GetRoad(RoadId{1U}));
}

TYPED_TEST(CrtpTest, LaneNeighbors) {
  decltype(auto) map = this->GetMap();

  for (auto road_id = RoadId{0U}; road_id <= RoadId{2U}; ++road_id) {
    auto road = map.GetRoad(road_id);
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

TYPED_TEST(CrtpTest, LaneLengthAndWidth) {
  decltype(auto) map = this->GetMap();

  for (auto road_id = RoadId{0U}; road_id <= RoadId{2U}; ++road_id) {
    auto road = map.GetRoad(road_id);
    ASSERT_TRUE(road);

    for (auto lane_id = LaneId{0U}; lane_id <= LaneId{2U}; ++lane_id) {
      auto lane = road->GetLane(LaneId{lane_id});
      ASSERT_TRUE(lane);

      ASSERT_DOUBLE_EQ(lane->GetLength(), TypeParam::MapFactoryType::kLaneLength);
      ASSERT_DOUBLE_EQ(lane->GetWidth(), TypeParam::MapFactoryType::kLaneWidth);
    }
  }
}
