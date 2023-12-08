#ifndef ORGANISM_H
#define ORGANISM_H


#include <vector>
    using std::vector;

#include <iostream>
    using std::ostream;

int const MOVE_UP = 0;
int const MOVE_RIGHT = 1;
int const MOVE_DOWN = 2;
int const MOVE_LEFT = 3;

class Organism
{
private:
    int stepsSinceBreed;        //Counter of steps since offpring production
    int breedingStepsNeeded;    //Counter os steps required to produce offsprings
    int simulationStep;         //Last simulation step that affected the organism

public:
    Organism();
    Organism(int breedingStepsNeeded);
    virtual ~Organism();

    Organism* breed();

    int getBreedingStepsNeeded() const;

    int getSimulationStep() const;
    void setSimulationStep(int sim) ;

    virtual Organism* getOffspring()=0;  //if breeds, returns a pointer to the offspring
    virtual int move()=0;               //returns the direction UP,DOWN,RIGHT,LEFT

    virtual int feed(bool up, bool down, bool left, bool right) =0; //feed
    virtual bool starve()=0;      //if true, then the critter starved and died.

    virtual std::string getRepresentation() const =0 ;  //String representation of the organism

    friend ostream& operator<<(ostream& out, const Organism& o);
};

#endif