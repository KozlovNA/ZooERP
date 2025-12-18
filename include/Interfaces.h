#pragma once
#include "ValueObjects.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////

class IAlive {
public:
  virtual Food GetFood() const = 0;
  virtual ~IAlive() = default;
};

//--------------------------------------------------------------------------//

class IInventory {
public:
  virtual int GetNumber() const = 0;
  virtual std::string GetName() const = 0;
  virtual ~IInventory() = default;
};
