#ifndef DB_H
#define DB_H

#include "Organism.h"

class DB : public Organism
{
private:
    int stepsSinceFeed; //Steps since last feeding.
    int starvingSteps;  //Steps without food before die.

public:
    DB();
    DB(int breedingStepsNeeded, int starvingSteps);
    virtual ~DB();


    virtual Organism* getOffspring() override;
    virtual int move() override;

    int feed(bool up, bool down, bool left, bool right);
    virtual bool starve()  override;

    virtual std::string getRepresentation() const;
};

#endif