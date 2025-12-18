#pragma once
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////

class Food {

private:

    int value;

//--------------------------------------------------------------------------//

public:

//--------------------------------------------------------------------------//

    explicit Food(int v) {
        if (v < 0) {
            throw std::invalid_argument("Количество еды не может быть отрицательным!");
        }
        value = v;
    }

//--------------------------------------------------------------------------//

    int kg() const { return value; }

//--------------------------------------------------------------------------//

    Food operator+(const Food& other) const {
        return Food(value + other.value);
    }

//--------------------------------------------------------------------------//

    Food& operator+=(const Food& other) {
        value += other.value;
        return *this;
    }
    
//--------------------------------------------------------------------------//

    bool operator==(const Food& other) const { return value == other.value; }

};

////////////////////////////////////////////////////////////////////////////////

class Kindness {

private:

    int value;

public:

//--------------------------------------------------------------------------//

    explicit Kindness(int v) {
        if (v < 0 || v > 10) {
            throw std::invalid_argument("Доброта должна быть от 0 до 10!");
        }
        value = v;
    }

//--------------------------------------------------------------------------//

    int Level() const { return value; }

//--------------------------------------------------------------------------//

    bool IsContactFriendly() const { return value > 5; }

//--------------------------------------------------------------------------//
    
    bool operator==(const Kindness& other) const { return value == other.value; }

};
