#include <gtest/gtest.h>

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

  auto GetMap() -> exceptions_map::Map& { return map_; }

 private:
  exceptions_map::Map map_{};
};

TEST_F(ExceptionsMapTest, RoadPredecessorsAndSuccessors) {
  ASSERT_EQ(GetMap().GetRoad(0).GetNextRoad(), GetMap().GetRoad(1));
  ASSERT_EQ(GetMap().GetRoad(1).GetNextRoad(), GetMap().GetRoad(2));
  ASSERT_EQ(GetMap().GetRoad(2).GetPreviousRoad(), GetMap().GetRoad(1));
  ASSERT_EQ(GetMap().GetRoad(1).GetPreviousRoad(), GetMap().GetRoad(0));
}

TEST_F(ExceptionsMapTest, LaneNeighbors) {
  ASSERT_EQ(GetMap().GetRoad(0).GetLane(0).GetRightLane(), GetMap().GetRoad(0).GetLane(1));
  ASSERT_EQ(GetMap().GetRoad(0).GetLane(1).GetRightLane(), GetMap().GetRoad(0).GetLane(2));
  ASSERT_EQ(GetMap().GetRoad(0).GetLane(2).GetLeftLane(), GetMap().GetRoad(0).GetLane(1));
  ASSERT_EQ(GetMap().GetRoad(0).GetLane(1).GetLeftLane(), GetMap().GetRoad(0).GetLane(0));

  ASSERT_EQ(GetMap().GetRoad(1).GetLane(0).GetRightLane(), GetMap().GetRoad(1).GetLane(1));
  ASSERT_EQ(GetMap().GetRoad(1).GetLane(1).GetRightLane(), GetMap().GetRoad(1).GetLane(2));
  ASSERT_EQ(GetMap().GetRoad(1).GetLane(2).GetLeftLane(), GetMap().GetRoad(1).GetLane(1));
  ASSERT_EQ(GetMap().GetRoad(1).GetLane(1).GetLeftLane(), GetMap().GetRoad(1).GetLane(0));

  ASSERT_EQ(GetMap().GetRoad(2).GetLane(0).GetRightLane(), GetMap().GetRoad(2).GetLane(1));
  ASSERT_EQ(GetMap().GetRoad(2).GetLane(1).GetRightLane(), GetMap().GetRoad(2).GetLane(2));
  ASSERT_EQ(GetMap().GetRoad(2).GetLane(2).GetLeftLane(), GetMap().GetRoad(2).GetLane(1));
  ASSERT_EQ(GetMap().GetRoad(2).GetLane(1).GetLeftLane(), GetMap().GetRoad(2).GetLane(0));
}

TEST_F(ExceptionsMapTest, LaneLengthAndWidth) {
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0).GetLane(0).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0).GetLane(1).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0).GetLane(2).GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1).GetLane(0).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1).GetLane(1).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1).GetLane(2).GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2).GetLane(0).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2).GetLane(1).GetLength(), kLaneLength);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2).GetLane(2).GetLength(), kLaneLength);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0).GetLane(0).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0).GetLane(1).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(0).GetLane(2).GetWidth(), kLaneWidth);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1).GetLane(0).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1).GetLane(1).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(1).GetLane(2).GetWidth(), kLaneWidth);

  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2).GetLane(0).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2).GetLane(1).GetWidth(), kLaneWidth);
  ASSERT_DOUBLE_EQ(GetMap().GetRoad(2).GetLane(2).GetWidth(), kLaneWidth);
}
