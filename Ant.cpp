
#include <cstdlib>
#include <vector>
    using std::vector;

#include <iostream>
    using std::ostream;

#include "Ant.h"

Ant::Ant(): Ant(0){};
Ant::Ant(int breedingStepsNeeded): Organism(breedingStepsNeeded)
{

};

Ant::~Ant(){/*left empty*/}

/*******************************************************************/
Organism* Ant::getOffspring()
{
    return new Ant(this->getBreedingStepsNeeded());
}

/*******************************************************************/
int Ant::move()
{
    int movement = rand() % 4;  //will produce 0,1,2,3

    return movement;
}

/*******************************************************************/
bool Ant::starve()
{   //so far, ants will not starve.
    return false;
}

/*******************************************************************/
int Ant::feed(bool up, bool down, bool left, bool right)
{
    return -1;
}

std::string Ant::getRepresentation() const
{
    return "O";
}