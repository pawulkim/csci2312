
#include <cstdlib>
#include <vector>
    using std::vector;

#include <iostream>
    using std::ostream;

#include "DB.h"

/*******************************************************************/
DB::DB(): DB(0,0){};

/*******************************************************************/
DB::DB(int breedingStepsNeeded, int starvingSteps):
    Organism(breedingStepsNeeded), starvingSteps{starvingSteps}, stepsSinceFeed{0}
{};

/*******************************************************************/
DB::~DB(){/*left empty*/}

/*******************************************************************/
Organism* DB::getOffspring()
{
    //offspring will be a new DB with same characteristics as this.
    return new DB(this->getBreedingStepsNeeded(), this->starvingSteps);
}

/*******************************************************************/
int DB::move()
{
    //Randomly move Up, right, down, left.
    int movement = rand() % 4;  //will produce 0,1,2,3
    return movement;
}

/*******************************************************************/
int DB::feed(bool up, bool down, bool left, bool right)
{
    //Parameters are provided by the world.
    //each indicate whether there is an ant in the given direction.

    if (up)
    {   //there's an ant up, so move there and eat it.
        this->stepsSinceFeed = 0;
        return MOVE_UP;
    }
    if (down)
    {
        this->stepsSinceFeed = 0;
        return MOVE_DOWN;
    }
    if (left)
    {
        this->stepsSinceFeed = 0;
        return MOVE_LEFT;
    }
    if (right)
    {
        this->stepsSinceFeed = 0;
        return MOVE_RIGHT;
    }
    //The movement pattern is up, then down, then left, then right.
    // can be improved with randoms

    this->stepsSinceFeed++; //Didn't eat (all four args were false)
    return -1; //invalid movement direction. Can be improved with exceptions.
}

/*******************************************************************/
bool DB::starve()
{
    //if there's been starvingSteps since last feed, then die.
    if (this->stepsSinceFeed >= this->starvingSteps)
        return true;
    else
        return false;
}


/*******************************************************************/
std::string DB::getRepresentation() const
{
    return "X";
}