// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <stdexcept>

#include "exceptions_map/lane.hpp"
#include "exceptions_map/map.hpp"
#include "exceptions_map/road.hpp"

class ExceptionsMapTest : public testing::Test {
 public:
  static constexpr auto kLaneWidth = 3.5;
  static constexpr auto kLaneLength = 100.0;

 protected:
  void SetUp() override {
    auto& road1 = map_.AddRoadBack();
    auto& road2 = map_.AddRoadBack();
    auto& road3 = map_.AddRoadBack();

    auto& lane11 = road1.AddLaneRight();
    auto& lane12 = road1.AddLaneRight();
    auto& lane13 = road1.AddLaneRight();

    auto& lane21 = road2.AddLaneRight();
    auto& lane22 = road2.AddLaneRight();
    auto& lane23 = road2.AddLaneRight();

    auto& lane31 = road3.AddLaneRight();
    auto& lane32 = road3.AddLaneRight();
    auto& lane33 = road3.AddLaneRight();

    lane11.SetLength(kLaneLength);
    lane12.SetLength(kLaneLength);
    lane13.SetLength(kLaneLength);

    lane21.SetLength(kLaneLength);
    lane22.SetLength(kLaneLength);
    lane23.SetLength(kLaneLength);

    lane31.SetLength(kLaneLength);
    lane32.SetLength(kLaneLength);
    lane33.SetLength(kLaneLength);

    lane11.SetWidth(kLaneWidth);
    lane12.SetWidth(kLaneWidth);
    lane13.SetWidth(kLaneWidth);

    lane21.SetWidth(kLaneWidth);
    lane22.SetWidth(kLaneWidth);
    lane23.SetWidth(kLaneWidth);

    lane31.SetWidth(kLaneWidth);
    lane32.SetWidth(kLaneWidth);
    lane33.SetWidth(kLaneWidth);
  }

  auto GetMap() -> gw::cpp_interface_techniques::exceptions_map::Map& { return map_; }

 private:
  gw::cpp_interface_techniques::exceptions_map::Map map_{};
};

TEST_F(ExceptionsMapTest, RoadPredecessorsAndSuccessors) {
  ASSERT_EQ(GetMap().GetRoad(0U).GetNextRoad(), GetMap().GetRoad(1U));
  ASSERT_EQ(GetMap().GetRoad(1U).GetNextRoad(), GetMap().GetRoad(2U));
  ASSERT_EQ(GetMap().GetRoad(2U).GetPreviousRoad(), GetMap().GetRoad(1U));
  ASSERT_EQ(GetMap().GetRoad(1U).GetPreviousRoad(), GetMap().GetRoad(0U));

  ASSERT_THROW(GetMap().GetRoad(3U), std::out_of_range);
}

TEST_F(ExceptionsMapTest, LaneNeighbors) {
  ASSERT_EQ(GetMap().GetRoad(0U).GetLane(0U).GetRightLane(), GetMap().GetRoad(0U).GetLane(1U));
  ASSERT_EQ(GetMap().GetRoad(0U).GetLane(1U).GetRightLane(), GetMap().GetRoad(0U).GetLane(2U));
  ASSERT_EQ(GetMap().GetRoad(0U).GetLane(2U).GetLeftLane(), GetMap().GetRoad(0U).GetLane(1U));
  ASSERT_EQ(GetMap().GetRoad(0U).GetLane(1U).GetLeftLane(), GetMap().GetRoad(0U).GetLane(0U));

  ASSERT_EQ(GetMap().GetRoad(1U).GetLane(0U).GetRightLane(), GetMap().GetRoad(1U).GetLane(1U));
  ASSERT_EQ(GetMap().GetRoad(1U).GetLane(1U).GetRightLane(), GetMap().GetRoad(1U).GetLane(2U));
  ASSERT_EQ(GetMap().GetRoad(1U).GetLane(2U).GetLeftLane(), GetMap().GetRoad(1U).GetLane(1U));
  ASSERT_EQ(GetMap().GetRoad(1U).GetLane(1U).GetLeftLane(), GetMap().GetRoad(1U).GetLane(0U));

  ASSERT_EQ(GetMap().GetRoad(2U).GetLane(0U).GetRightLane(), GetMap().GetRoad(2U).GetLane(1U));
  ASSERT_EQ(GetMap().GetRoad(2U).GetLane(1U).GetRightLane(), GetMap().GetRoad(2U).GetLane(2U));
  ASSERT_EQ(GetMap().GetRoad(2U).GetLane(2U).GetLeftLane(), GetMap().GetRoad(2U).GetLane(1U));
  ASSERT_EQ(GetMap().GetRoad(2U).GetLane(1U).GetLeftLane(), GetMap().GetRoad(2U).GetLane(0U));
}

TEST_F(ExceptionsMapTest, LaneLengthAndWidth) {
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).GetLane(0U).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).GetLane(1U).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).GetLane(2U).GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).GetLane(0U).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).GetLane(1U).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).GetLane(2U).GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).GetLane(0U).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).GetLane(1U).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).GetLane(2U).GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).GetLane(0U).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).GetLane(1U).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).GetLane(2U).GetWidth(), kLaneWidth);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).GetLane(0U).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).GetLane(1U).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).GetLane(2U).GetWidth(), kLaneWidth);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).GetLane(0U).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).GetLane(1U).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).GetLane(2U).GetWidth(), kLaneWidth);
}
