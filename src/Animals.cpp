#include "Animals.h"

////////////////////////////////////////////////////////////////////////////////

Animal::Animal(int num, Food f, std::string speciesName)
    : number(num), food(f), name(std::move(speciesName)) {}

//--------------------------------------------------------------------------//

Food Animal::GetFood() const { return food; }

//--------------------------------------------------------------------------//

int Animal::GetNumber() const { return number; }

//--------------------------------------------------------------------------//

std::string Animal::GetName() const { return name; }

////////////////////////////////////////////////////////////////////////////////

Herbo::Herbo(int num, Food f, std::string n, Kindness k)
    : Animal(num, f, std::move(n)), kindness(k) {}

//--------------------------------------------------------------------------//

Kindness Herbo::GetKindness() const { return kindness; }

//--------------------------------------------------------------------------//

bool Herbo::CanBeInContactZoo() const { return kindness.IsContactFriendly(); }

////////////////////////////////////////////////////////////////////////////////

Predator::Predator(int num, Food f, std::string n)
    : Animal(num, f, std::move(n)) {}

////////////////////////////////////////////////////////////////////////////////

Monkey::Monkey(int num, Food f, Kindness k) : Herbo(num, f, "Обезьяна", k) {}

////////////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(int num, Food f, Kindness k) : Herbo(num, f, "Кролик", k) {}

////////////////////////////////////////////////////////////////////////////////

Tiger::Tiger(int num, Food f) : Predator(num, f, "Тигр") {}

////////////////////////////////////////////////////////////////////////////////

Wolf::Wolf(int num, Food f) : Predator(num, f, "Волк") {}
