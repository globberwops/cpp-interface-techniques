// Copyright (c) 2023 Martin Stump
// SPDX-License-Identifier: BSL-1.0

#include <gtest/gtest.h>

#include <stdexcept>

#include "exceptions_map/lane.hpp"
#include "exceptions_map/map.hpp"
#include "exceptions_map/road.hpp"

class ExceptionsMapTest : public testing::Test {
 protected:
  void SetUp() override { map_ = gw::cpp_interface_techniques::exceptions_map::MapFactory::Create(); }

  auto GetMap() -> gw::cpp_interface_techniques::exceptions_map::Map& { return map_; }

 private:
  gw::cpp_interface_techniques::exceptions_map::Map map_{};
};

TEST_F(ExceptionsMapTest, RoadPredecessorsAndSuccessors) {
  ASSERT_EQ(GetMap().GetRoad(0U).get().GetNextRoad().get(), GetMap().GetRoad(1U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetNextRoad().get(), GetMap().GetRoad(2U).get());
  ASSERT_EQ(GetMap().GetRoad(2U).get().GetPreviousRoad().get(), GetMap().GetRoad(1U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetPreviousRoad().get(), GetMap().GetRoad(0U).get());

  ASSERT_THROW(GetMap().GetRoad(3U), std::out_of_range);
}

TEST_F(ExceptionsMapTest, LaneNeighbors) {
  ASSERT_EQ(GetMap().GetRoad(0U).get().GetLane(0U).get().GetRightLane().get(),
            GetMap().GetRoad(0U).get().GetLane(1U).get());
  ASSERT_EQ(GetMap().GetRoad(0U).get().GetLane(1U).get().GetRightLane().get(),
            GetMap().GetRoad(0U).get().GetLane(2U).get());
  ASSERT_EQ(GetMap().GetRoad(0U).get().GetLane(2U).get().GetLeftLane().get(),
            GetMap().GetRoad(0U).get().GetLane(1U).get());
  ASSERT_EQ(GetMap().GetRoad(0U).get().GetLane(1U).get().GetLeftLane().get(),
            GetMap().GetRoad(0U).get().GetLane(0U).get());

  ASSERT_EQ(GetMap().GetRoad(1U).get().GetLane(0U).get().GetRightLane().get(),
            GetMap().GetRoad(1U).get().GetLane(1U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetLane(1U).get().GetRightLane().get(),
            GetMap().GetRoad(1U).get().GetLane(2U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetLane(2U).get().GetLeftLane().get(),
            GetMap().GetRoad(1U).get().GetLane(1U).get());
  ASSERT_EQ(GetMap().GetRoad(1U).get().GetLane(1U).get().GetLeftLane().get(),
            GetMap().GetRoad(1U).get().GetLane(0U).get());

  ASSERT_EQ(GetMap().GetRoad(2U).get().GetLane(0U).get().GetRightLane().get(),
            GetMap().GetRoad(2U).get().GetLane(1U).get());
  ASSERT_EQ(GetMap().GetRoad(2U).get().GetLane(1U).get().GetRightLane().get(),
            GetMap().GetRoad(2U).get().GetLane(2U).get());
  ASSERT_EQ(GetMap().GetRoad(2U).get().GetLane(2U).get().GetLeftLane().get(),
            GetMap().GetRoad(2U).get().GetLane(1U).get());
  ASSERT_EQ(GetMap().GetRoad(2U).get().GetLane(1U).get().GetLeftLane().get(),
            GetMap().GetRoad(2U).get().GetLane(0U).get());
}

TEST_F(ExceptionsMapTest, LaneLengthAndWidth) {
  const auto& kLaneLength = gw::cpp_interface_techniques::exceptions_map::MapFactory::kLaneLength;
  const auto& kLaneWidth = gw::cpp_interface_techniques::exceptions_map::MapFactory::kLaneWidth;

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).get().GetLane(0U).get().GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).get().GetLane(1U).get().GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).get().GetLane(2U).get().GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).get().GetLane(0U).get().GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).get().GetLane(1U).get().GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).get().GetLane(2U).get().GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).get().GetLane(0U).get().GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).get().GetLane(1U).get().GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).get().GetLane(2U).get().GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).get().GetLane(0U).get().GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).get().GetLane(1U).get().GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0U).get().GetLane(2U).get().GetWidth(), kLaneWidth);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).get().GetLane(0U).get().GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).get().GetLane(1U).get().GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1U).get().GetLane(2U).get().GetWidth(), kLaneWidth);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).get().GetLane(0U).get().GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).get().GetLane(1U).get().GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2U).get().GetLane(2U).get().GetWidth(), kLaneWidth);
}
