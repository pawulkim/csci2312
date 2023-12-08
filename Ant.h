#ifndef ANT_H
#define ANT_H

#include "Organism.h"

class Ant : public Organism
{
private:
    /*Nothing here.*/

public:
    Ant();
    Ant(int breedingStepsNeeded);
    virtual ~Ant();

    virtual Organism* getOffspring() override;
    virtual int move() override;

    //Override but do nothing.
    virtual bool starve()  override;
    int feed(bool up, bool down, bool left, bool right) override;

    virtual std::string getRepresentation() const;
};

#endif