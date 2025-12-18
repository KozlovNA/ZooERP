#pragma once
#include "Interfaces.h"
#include "ValueObjects.h"

////////////////////////////////////////////////////////////////////////////////

class Animal : public IAlive, public IInventory {

protected:

    Food food;
    int number;
    std::string name;

//--------------------------------------------------------------------------//

public:

//--------------------------------------------------------------------------//

    Animal(int num, Food food, std::string speciesName);

//--------------------------------------------------------------------------//

    Food GetFood() const override;

//--------------------------------------------------------------------------//

    int GetNumber() const override;

//--------------------------------------------------------------------------//

    std::string GetName() const override;

};

////////////////////////////////////////////////////////////////////////////////

class Herbo : public Animal {
  
protected:

    Kindness kindness; 

//--------------------------------------------------------------------------//

public:

//--------------------------------------------------------------------------//

    Herbo(int num, Food food, std::string n, Kindness k);

//--------------------------------------------------------------------------//

    Kindness GetKindness() const;

//--------------------------------------------------------------------------//

    bool CanBeInContactZoo() const;

};

////////////////////////////////////////////////////////////////////////////////

class Predator : public Animal {

public:

    Predator(int num, Food food, std::string n);

};

////////////////////////////////////////////////////////////////////////////////

class Monkey : public Herbo {

public:
  
    Monkey(int num, Food food, Kindness kindness);

};

////////////////////////////////////////////////////////////////////////////////

class Rabbit : public Herbo {

public:

    Rabbit(int num, Food food, Kindness kindness);

};

////////////////////////////////////////////////////////////////////////////////

class Tiger : public Predator {

public:

    Tiger(int num, Food food);

};

////////////////////////////////////////////////////////////////////////////////

class Wolf : public Predator {

public:

    Wolf(int num, Food food);

};
