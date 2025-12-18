#pragma once
#include "Animals.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class IVetClinic {

public:
  
//--------------------------------------------------------------------------//

    virtual bool CheckHealth(Animal* animal) = 0;

//--------------------------------------------------------------------------//

    virtual ~IVetClinic() = default;

};

////////////////////////////////////////////////////////////////////////////////

class VetClinic : public IVetClinic {

public:

//--------------------------------------------------------------------------//

    bool CheckHealth(Animal* animal) override {
        std::cout << "Ветклиника: Проверка здоровья " << animal->GetName() 
                  << " (ID: " << animal->GetNumber() << ")...\n";
        return true; 
    }

};
