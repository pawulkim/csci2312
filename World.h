#ifndef WORLD_H
#define WORLD_H

#include <array>
    using std::array;

#include <iostream>
    using std::ostream;

#include "Organism.h"
#include "Ant.h"

int const WORLD_SIZE = 5;   //Size of the world. Problem defaulted to 20x20
int const WORLD_ANTS = 10;  //Initial number of ants
int const WORLD_DB = 3;     //Initial number of Doodlebugs.

class World
{
private:
    array< array<Organism*, WORLD_SIZE>, WORLD_SIZE> antSpace;  //store ants
    array< array<Organism*, WORLD_SIZE>, WORLD_SIZE> dbSpace;   //store doodlebugs
    //These two arrays are handled in parallel. I.e., a cell [x,y] will be the interception
    //of antSpace[x][y] and dbSpace[x][y]. One of them (or both) must be nullptr!.


    int simulationStep; //store the simulation step

    void getNewCoordinates(int shift, int& x, int& y);
    //helper function to computer coordinates given a shift. It's private

public:
    World();
    virtual ~World();

    void simulate(); //main simulation funciton.

    friend ostream& operator<<(ostream& out, const World& w);
};
#endif