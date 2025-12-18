#pragma once
#include "Zoo.h"
#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

class MenuContext;

////////////////////////////////////////////////////////////////////////////////

class IMenuState {

public:
  virtual ~IMenuState() = default;

  //--------------------------------------------------------------------------//

  virtual void Process(MenuContext &context) = 0;
};

////////////////////////////////////////////////////////////////////////////////

class MenuContext {

private:
  std::shared_ptr<Zoo> zoo;
  std::shared_ptr<IMenuState> currentState;
  bool isRunning = true;

  //--------------------------------------------------------------------------//

public:
  explicit MenuContext(std::shared_ptr<Zoo> z);

  //--------------------------------------------------------------------------//

  void SetState(std::shared_ptr<IMenuState> newState);

  //--------------------------------------------------------------------------//

  std::shared_ptr<Zoo> GetZoo() const;

  //--------------------------------------------------------------------------//

  bool IsRunning() const;

  //--------------------------------------------------------------------------//

  void Exit();

  //--------------------------------------------------------------------------//

  void Run();
};

////////////////////////////////////////////////////////////////////////////////

class MainMenuState : public IMenuState {
public:
  void Process(MenuContext &context) override;
};

////////////////////////////////////////////////////////////////////////////////

class AddAnimalState : public IMenuState {
public:
  void Process(MenuContext &context) override;
};

////////////////////////////////////////////////////////////////////////////////

class AddThingState : public IMenuState {
public:
  void Process(MenuContext &context) override;
};

////////////////////////////////////////////////////////////////////////////////

class ReportState : public IMenuState {
public:
  void Process(MenuContext &context) override;
};
