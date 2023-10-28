#include <gtest/gtest.h>

#include "optional_map/lane.hpp"
#include "optional_map/map.hpp"
#include "optional_map/road.hpp"

class OptionalMapTest : public testing::Test {
 public:
  static constexpr auto kLaneWidth = 3.5;
  static constexpr auto kLaneLength = 100.0;

 protected:
  void SetUp() override {
    for (auto i = 0U; i <= 2; ++i) {
      auto road = map_.AddRoadBack();

      for (auto j = 0U; j <= 2; ++j) {
        road.and_then([](auto road) { return road.get().AddLaneRight(); }).and_then([](auto lane) {
          lane.get().SetLength(kLaneLength);
          lane.get().SetWidth(kLaneWidth);
          return std::make_optional(lane);
        });
      }
    }
  }

  auto GetMap() -> optional_map::Map& { return map_; }

 private:
  optional_map::Map map_{};
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
    ASSERT_TRUE(GetMap().GetRoad(i));
    auto& road = GetMap().GetRoad(i)->get();

    for (auto j = 0U; j <= 2; ++j) {
      ASSERT_TRUE(road.GetLane(j));
      auto& lane = road.GetLane(j)->get();

      ASSERT_DOUBLE_EQ(lane.GetLength(), kLaneLength);
      ASSERT_DOUBLE_EQ(lane.GetWidth(), kLaneWidth);
    }
  }
}
