#include "../include/Animals.h"
#include "../include/Things.h"
#include "../include/ValueObjects.h" // Подключаем
#include "../include/Zoo.h"
#include <gtest/gtest.h>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

class MockVetClinic : public IVetClinic {
public:
  bool shouldBeHealthy = true;

  bool CheckHealth(Animal *animal) override { return shouldBeHealthy; }
};

////////////////////////////////////////////////////////////////////////////////

class ZooTest : public ::testing::Test {
protected:
  std::shared_ptr<MockVetClinic> mockVet;
  std::shared_ptr<Zoo> zoo;

  void SetUp() override {
    mockVet = std::make_shared<MockVetClinic>();
    zoo = std::make_shared<Zoo>(mockVet);
  }
};

////////////////////////////////////////////////////////////////////////////////

TEST(ValueObjectTest, Validation) {
  // Kindness
  EXPECT_THROW(Kindness(11), std::invalid_argument);
  EXPECT_THROW(Kindness(-1), std::invalid_argument);
  EXPECT_NO_THROW(Kindness(5));

  // Food
  EXPECT_THROW(Food(-5), std::invalid_argument);
  EXPECT_NO_THROW(Food(10));
}

//--------------------------------------------------------------------------//

TEST_F(ZooTest, CalculateTotalFood) {
  auto monkey = std::make_shared<Monkey>(1, Food(10), Kindness(7));
  auto tiger = std::make_shared<Tiger>(2, Food(20));

  zoo->AddAnimal(monkey);
  zoo->AddAnimal(tiger);

  zoo->AddThing(std::make_shared<Table>(3));

  ASSERT_EQ(zoo->CalculateTotalFood(), 30);
}

//--------------------------------------------------------------------------//

TEST_F(ZooTest, ContactZooFilter) {
  auto kindRabbit = std::make_shared<Rabbit>(1, Food(5), Kindness(10));
  auto evilRabbit = std::make_shared<Rabbit>(2, Food(5), Kindness(1));
  auto wolf = std::make_shared<Wolf>(3, Food(10));

  zoo->AddAnimal(kindRabbit);
  zoo->AddAnimal(evilRabbit);
  zoo->AddAnimal(wolf);

  auto list = zoo->GetContactZooList();

  ASSERT_EQ(list.size(), 1);
  EXPECT_EQ(list[0]->GetNumber(), 1);
}

//--------------------------------------------------------------------------//

TEST_F(ZooTest, VetClinicRejection) {
  mockVet->shouldBeHealthy = false;

  auto wolf = std::make_shared<Wolf>(1, Food(20));

  EXPECT_FALSE(zoo->AddAnimal(wolf));
  EXPECT_EQ(zoo->CalculateTotalFood(), 0);
}
