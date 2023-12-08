

#include <vector>
    using std::vector;

#include <iostream>
    using std::ostream;

#include "Organism.h"

/*********************************************************************************************************/
Organism::Organism(): Organism(0){};
/*********************************************************************************************************/
Organism::Organism(int breedingStepsNeeded)
: breedingStepsNeeded{breedingStepsNeeded}, simulationStep{0}, stepsSinceBreed{0}
{
}

/*********************************************************************************************************/
Organism::~Organism(){/*left empty*/}

/*********************************************************************************************************/
int Organism::getBreedingStepsNeeded() const
{
    return this->breedingStepsNeeded;
}

/*********************************************************************************************************/
int Organism::getSimulationStep() const
{
    return this->simulationStep;
}
/*********************************************************************************************************/
void Organism::setSimulationStep(int sim)
{
    this->simulationStep = sim;
}


/*********************************************************************************************************/
Organism* Organism::breed()
{
    this->stepsSinceBreed++;

    if (this->stepsSinceBreed == this->breedingStepsNeeded)
    {   //need offspring
        this->stepsSinceBreed = 0;
        return this->getOffspring(); //this is virtual. will be determined by the derived class
    }

    return nullptr;  //no offspring produced.
};

/*********************************************************************************************************/
ostream& operator<<(ostream& out, const Organism& o)
{
    out << o.getRepresentation();
    return out;
}