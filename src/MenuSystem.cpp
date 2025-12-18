#include "MenuSystem.h"
#include "Animals.h"
#include "Things.h"
#include <cstdlib>
#include <limits>

////////////////////////////////////////////////////////////////////////////////

void ClearScreen() {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

////////////////////////////////////////////////////////////////////////////////

void WaitForKey() {
  std::cout << "\nНажмите Enter, чтобы продолжить...";
  std::cin.get();
}

////////////////////////////////////////////////////////////////////////////////

int ReadInt() {
  std::string line;
  while (true) {
    if (!std::getline(std::cin, line) || line.empty()) {
      continue;
    }

    try {
      size_t pos;
      int val = std::stoi(line, &pos);

      if (pos < line.size()) {
        bool hasGarbage = false;
        for (size_t i = pos; i < line.size(); ++i) {
          if (!std::isspace(line[i])) {
            hasGarbage = true;
            break;
          }
        }
        if (hasGarbage) {
          throw std::invalid_argument("Лишние символы");
        }
      }

      return val;
    } catch (...) {
      std::cout << "Некорректный ввод (введите только целое число): ";
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

Food ReadFood() {
  while (true) {
    std::cout << "Количество еды (кг): ";
    int val = ReadInt();
    try {
      return Food(val);
    } catch (const std::exception &e) {
      std::cout << "[ОШИБКА] " << e.what() << " Попробуйте снова.\n";
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

Kindness ReadKindness() {
  while (true) {
    std::cout << "Уровень доброты (0-10): ";
    int val = ReadInt();
    try {
      return Kindness(val);
    } catch (const std::exception &e) {
      std::cout << "[ОШИБКА] " << e.what() << " Попробуйте снова.\n";
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

MenuContext::MenuContext(std::shared_ptr<Zoo> z) : zoo(std::move(z)) {
  currentState = std::make_shared<MainMenuState>();
}

//--------------------------------------------------------------------------//

void MenuContext::SetState(std::shared_ptr<IMenuState> newState) {
  currentState = std::move(newState);
}

//--------------------------------------------------------------------------//

std::shared_ptr<Zoo> MenuContext::GetZoo() const { return zoo; }

//--------------------------------------------------------------------------//

bool MenuContext::IsRunning() const { return isRunning; }

//--------------------------------------------------------------------------//

void MenuContext::Exit() { isRunning = false; }

//--------------------------------------------------------------------------//

void MenuContext::Run() {
  while (isRunning && currentState) {
    currentState->Process(*this);
  }
}

////////////////////////////////////////////////////////////////////////////////

void MainMenuState::Process(MenuContext &context) {
  ClearScreen();
  std::cout << "===    ZooERP    ===\n";
  std::cout << "1. Добавить животное\n";
  std::cout << "2. Добавить вещь\n";
  std::cout << "3. Просмотр отчетов\n";
  std::cout << "0. Выход\n";
  std::cout << "> ";

  int choice = ReadInt();

  switch (choice) {
  case 1:
    context.SetState(std::make_shared<AddAnimalState>());
    break;
  case 2:
    context.SetState(std::make_shared<AddThingState>());
    break;
  case 3:
    context.SetState(std::make_shared<ReportState>());
    break;
  case 0:
    context.Exit();
    break;
  default:
    break;
  }
}

////////////////////////////////////////////////////////////////////////////////

void AddAnimalState::Process(MenuContext &context) {
  ClearScreen();
  static int nextId = 100;

  std::cout << "--- Добавление животного ---\n";
  std::cout << "Тип: 1-Обезьяна, 2-Кролик, 3-Тигр, 4-Волк (0-Отмена)\n> ";
  int type = ReadInt();

  if (type == 0) {
    context.SetState(std::make_shared<MainMenuState>());
    return;
  }

  Food food = ReadFood();
  std::shared_ptr<Animal> animal;

  if (type == 1 || type == 2) {
    Kindness kindness = ReadKindness();

    if (type == 1)
      animal = std::make_shared<Monkey>(nextId++, food, kindness);
    else
      animal = std::make_shared<Rabbit>(nextId++, food, kindness);
  } else if (type == 3)
    animal = std::make_shared<Tiger>(nextId++, food);
  else if (type == 4)
    animal = std::make_shared<Wolf>(nextId++, food);

  std::cout << "\n-----------------\n";
  if (animal) {
    if (context.GetZoo()->AddAnimal(animal)) {
      std::cout << "[УСПЕХ] Животное принято на баланс!\n";
    } else {
      std::cout << "[ОТКАЗ] Ветклиника: животное не здорово.\n";
    }
  } else {
    std::cout << "[ОШИБКА] Неверный тип животного.\n";
  }

  WaitForKey();
  context.SetState(std::make_shared<MainMenuState>());
}

////////////////////////////////////////////////////////////////////////////////

void AddThingState::Process(MenuContext &context) {
  ClearScreen();
  static int nextThingId = 200;

  std::cout << "--- Добавление вещи ---\n";
  std::cout << "Тип: 1-Стол, 2-Компьютер (0-Отмена)\n> ";
  int type = ReadInt();

  if (type == 0) {
    context.SetState(std::make_shared<MainMenuState>());
    return;
  }

  if (type == 1) {
    context.GetZoo()->AddThing(std::make_shared<Table>(nextThingId++));
    std::cout << "[УСПЕХ] Стол добавлен.\n";
  } else if (type == 2) {
    context.GetZoo()->AddThing(std::make_shared<Computer>(nextThingId++));
    std::cout << "[УСПЕХ] Компьютер добавлен.\n";
  } else {
    std::cout << "[ОШИБКА] Неверный тип.\n";
  }

  WaitForKey();
  context.SetState(std::make_shared<MainMenuState>());
}

////////////////////////////////////////////////////////////////////////////////

void ReportState::Process(MenuContext &context) {
  ClearScreen();
  std::cout << "--- ОТЧЕТЫ ---\n";
  std::cout << "1. Потребление еды\n";
  std::cout << "2. Контактный зоопарк\n";
  std::cout << "3. Инвентаризация\n";
  std::cout << "0. Назад\n> ";

  int choice = ReadInt();
  auto zoo = context.GetZoo();

  if (choice == 0) {
    context.SetState(std::make_shared<MainMenuState>());
    return;
  }

  ClearScreen();
  if (choice == 1) {
    std::cout << "Всего требуется еды: " << zoo->CalculateTotalFood()
              << " кг/день\n";
  } else if (choice == 2) {
    std::cout << "Животные для контактного зоопарка:\n";
    for (const auto &h : zoo->GetContactZooList()) {
      std::cout << "- " << h->GetName() << " (ID: " << h->GetNumber() << ")\n";
    }
  } else if (choice == 3) {
    zoo->PrintInventory();
  }

  WaitForKey();
}
