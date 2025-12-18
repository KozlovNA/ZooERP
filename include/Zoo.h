#pragma once
#include <vector>
#include <memory>
#include "Interfaces.h"
#include "Animals.h"
#include "Things.h"
#include "VetClinic.h"

////////////////////////////////////////////////////////////////////////////////

class Zoo {

private:

    std::vector<std::shared_ptr<IInventory>> inventory;
    std::shared_ptr<IVetClinic> vetClinic;

public:

//--------------------------------------------------------------------------//

    Zoo(std::shared_ptr<IVetClinic> clinic);

//--------------------------------------------------------------------------//

    bool AddAnimal(std::shared_ptr<Animal> animal);

//--------------------------------------------------------------------------//

    void AddThing(std::shared_ptr<Thing> thing);

//--------------------------------------------------------------------------//
    
    int CalculateTotalFood() const;

//--------------------------------------------------------------------------//

    std::vector<std::shared_ptr<Herbo>> GetContactZooList() const;

//--------------------------------------------------------------------------//

    void PrintInventory() const;

};
