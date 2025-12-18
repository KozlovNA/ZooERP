#pragma once
#include "Interfaces.h"

////////////////////////////////////////////////////////////////////////////////

class Thing : public IInventory {

protected:

    int number;
    std::string name;

//--------------------------------------------------------------------------//

public:

    Thing(int num, std::string n) : number(num), name(std::move(n)) {}

//--------------------------------------------------------------------------//

    int GetNumber() const override { return number; }

//--------------------------------------------------------------------------//

    std::string GetName() const override { return name; }

};

////////////////////////////////////////////////////////////////////////////////

class Table : public Thing {
public:
    Table(int num) : Thing(num, "Стол") {}
};

////////////////////////////////////////////////////////////////////////////////

class Computer : public Thing {
public:
    Computer(int num) : Thing(num, "Компьютер") {}
};
