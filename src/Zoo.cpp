#include "Zoo.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Zoo::Zoo(std::shared_ptr<IVetClinic> clinic) : vetClinic(std::move(clinic)) {}

bool Zoo::AddAnimal(std::shared_ptr<Animal> animal) {
  if (vetClinic->CheckHealth(animal.get())) {
    inventory.push_back(animal);
    return true;
  }
  return false;
}

//--------------------------------------------------------------------------//

void Zoo::AddThing(std::shared_ptr<Thing> thing) { inventory.push_back(thing); }

//--------------------------------------------------------------------------//

int Zoo::CalculateTotalFood() const {
  Food total(0);
  for (const auto &item : inventory) {
    if (auto alive = std::dynamic_pointer_cast<IAlive>(item)) {
      total += alive->GetFood();
    }
  }
  return total.kg();
}

//--------------------------------------------------------------------------//

std::vector<std::shared_ptr<Herbo>> Zoo::GetContactZooList() const {
  std::vector<std::shared_ptr<Herbo>> result;
  for (const auto &item : inventory) {
    if (auto herbo = std::dynamic_pointer_cast<Herbo>(item)) {
      if (herbo->CanBeInContactZoo()) {
        result.push_back(herbo);
      }
    }
  }
  return result;
}

//--------------------------------------------------------------------------//

void Zoo::PrintInventory() const {
  std::cout << "\n--- Инвентаризация ---\n";
  for (const auto &item : inventory) {
    std::cout << "ID: " << item->GetNumber() << " | Тип: " << item->GetName();
    if (std::dynamic_pointer_cast<Animal>(item))
      std::cout << " (Животное)";
    else
      std::cout << " (Предмет)";
    std::cout << std::endl;
  }
  std::cout << "----------------------\n";
}
