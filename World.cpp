#include <cstdlib>
#include <array>
    using std::array;

#include <iostream>
    using std::ostream;

#include "World.h"
#include "Organism.h"
#include "Ant.h"
#include "DB.h"

/*************************************************************************/
World::World()
: simulationStep{0}
{
    /** Add Ants to World.  */
    for (size_t i{0}; i<WORLD_ANTS; i++)
    {
        bool added = false;
        int x,y;

        while (!added)
        {
            x = rand()%WORLD_SIZE;
            y = rand()%WORLD_SIZE;

            if (antSpace[x][y] == nullptr)
            {
                antSpace[x][y] = new Ant(3);
                added = true;
            }
        }
    }

    /** Add DB to World.  */
    for (size_t i{0}; i<WORLD_DB; i++)
    {
        bool added = false;
        int x,y;

        while (!added)
        {
            x = rand()%WORLD_SIZE;
            y = rand()%WORLD_SIZE;

            if ((antSpace[x][y] == nullptr) && (dbSpace[x][y] == nullptr))
            {
                dbSpace[x][y] = new DB(8,3);
                added = true;
            }
        }
    }
}
/*************************************************************************/
World::~World()
{   //Delete Objects
    for (size_t x{0}; x<WORLD_SIZE; x++)
    {
        for (size_t y{0}; y<WORLD_SIZE; y++)
        {
            if (this->antSpace[x][y] != nullptr)
                delete this->antSpace[x][y];
            if (this->dbSpace[x][y] != nullptr)
                delete this->dbSpace[x][y];
        }
    }
}

/*************************************************************************/
ostream& operator<<(ostream& out, const World& w)
{
    int totalAnts{0}, totalDB{0};
    for (size_t x{0}; x<WORLD_SIZE; x++)
    {
        for (size_t y{0}; y<WORLD_SIZE; y++)
        {
            out << " | ";
            if (w.antSpace[x][y] != nullptr)
            {
                out << *(w.antSpace[x][y]);
                totalAnts++;
            }
            else if (w.dbSpace[x][y] != nullptr)
            {
                out << *(w.dbSpace[x][y]);
                totalDB++;
            }
            else
                out << ' ';
        }
        out << " |\n";
    }
    out << "Total Ants:" << totalAnts << " Total DB:" << totalDB << std::endl;
    return out;
}

/*************************************************************************/
void World::getNewCoordinates(int shift, int& x, int& y)
{
    switch (shift)
    {
        case MOVE_UP:
            x--;
            break;

        case MOVE_DOWN:
            x++;
            break;

        case MOVE_RIGHT:
            y++;
            break;

        case MOVE_LEFT:
            y--;
            break;
    }
}

/*************************************************************************/
void World::simulate()
{
    this->simulationStep++; //new simulation step. increase counter.

    //////////////////////////////////////////////////
    /////////////////// Doodlebugs //////////////////
    //////////////////////////////////////////////////
    for (int x{0}; x<WORLD_SIZE; x++)
    {
        for (int y{0}; y<WORLD_SIZE; y++)
        {
            if (this->dbSpace[x][y] != nullptr &&
                this->dbSpace[x][y]->getSimulationStep() < this->simulationStep)
            {
                //mark the DB simulation step. this prevents to double simulate if the
                //critter moves down in the grid.
                this->dbSpace[x][y]->setSimulationStep(this->simulationStep);

                /*Feed  and Move*/

                int feed;
                bool left  = ((y-1)>=0 && (this->antSpace[x][y-1]!=nullptr));
                bool up    = ((x-1)>=0 && (this->antSpace[x-1][y]!=nullptr));
                bool right = ((y+1)<WORLD_SIZE && (this->antSpace[x][y+1]!=nullptr));
                bool down  = ((x+1)<WORLD_SIZE && (this->antSpace[x+1][y]!=nullptr)) ;

                //these are the current and future coord for the DB.
                //as after moving it might change (or not)
                int newX{x};
                int newY{y};

                feed = this->dbSpace[x][y]->feed( up,down , left , right);
                if (feed >= 0)
                {   //feed has the movement. DB ready to eat an ant.
                    this->getNewCoordinates(feed,newX, newY);

                    //remove ant.
                    delete this->antSpace[newX][newY];
                    this->antSpace[newX][newY] = nullptr;
                }
                else
                {   //no feed (no ant was close). let's try move.
                    int move = this->dbSpace[x][y]->move();
                    this->getNewCoordinates(move, newX, newY);
                }
                //Either because the DB ate an ant or moved.
                if ( newX >= 0 && newX < WORLD_SIZE && //check bounds
                     newY >= 0 && newY < WORLD_SIZE &&
                     this->antSpace[newX][newY] == nullptr && //cell free from ants
                     this->dbSpace[newX][newY] == nullptr     //cell free from DB
                    )
                {
                    this->dbSpace[newX][newY] = this->dbSpace[x][y];
                    this->dbSpace[x][y] = nullptr;
                }
                else
                {
                    //it was not possible to move, so rever newX and newY to x,y
                    newX = x;
                    newY = y;
                }

                /*      BREED       */
                Organism* offspring{nullptr};
                bool placed{false};

                offspring = this->dbSpace[newX][newY]->breed();

                if (offspring != nullptr)
                {   // we have the offspring, now we need to place it or destroy it.
                    int offspringX = newX;
                    int offspringY = newY;

                    for (int shift{0}; shift<4; shift++) //look for a position up, right, down, or left
                    {
                        this->getNewCoordinates(shift,offspringX, offspringY);

                        if (newX >= 0 && newX < WORLD_SIZE &&                    //check bounds
                            newY >= 0 && newY < WORLD_SIZE &&
                            this->antSpace[offspringX][offspringY] == nullptr && //no ants in [offspringX,offspringY]
                            this->dbSpace[offspringX][offspringY] == nullptr     //no DB in [offspringX,offspringY]
                            )
                        {   //found place.
                            this->dbSpace[offspringX][offspringY] = offspring;
                            placed = true;
                            break; //placed the offspring. terminates shift for loop.
                        }
                    }
                    if (!placed)
                    {
                        delete offspring; //no free space for the offspring
                        offspring = nullptr;
                    }
                }

                /*      STARVE.      */
                if (this->dbSpace[newX][newY]->starve() )
                {
                    delete this->dbSpace[newX][newY];
                    this->dbSpace[newX][newY] = nullptr;
                }
            }
        }
    }


    //////////////////////////////////////////////////
    ////////////////////// ANTS //////////////////////
    //////////////////////////////////////////////////
    for (int x{0}; x<WORLD_SIZE; x++)
    {
        for (int y{0}; y<WORLD_SIZE; y++)
        {
            if (this->antSpace[x][y] != nullptr &&
                this->antSpace[x][y]->getSimulationStep() < this->simulationStep)
            {
                this->antSpace[x][y]->setSimulationStep(this->simulationStep);

                /*     MOVE ANTS. */
                int newX{x};
                int newY{y};

                int shift = this->antSpace[x][y]->move();
                this->getNewCoordinates(shift,newX, newY);

                if ( newX >= 0 && newX < WORLD_SIZE &&          //check bounds
                     newY >= 0 && newY < WORLD_SIZE &&
                     this->antSpace[newX][newY] == nullptr &&   //cell free from ants
                     this->dbSpace[newX][newY] == nullptr       //cell free from DB
                    )
                {   //move the ant.
                    this->antSpace[newX][newY] = this->antSpace[x][y];
                    this->antSpace[x][y] = nullptr;
                }
                else
                {
                    //it was not possible to move, so revert newX and newY to x,y
                    newX = x;
                    newY = y;
                }

                ///////////////////////// BREED
                Organism* offspring{nullptr};
                bool placed{false};
                offspring = this->antSpace[newX][newY]->breed();

                if (offspring != nullptr)
                {
                    int offspringX{newX};
                    int offspringY{newY};

                    for (int shift{0}; shift<4; shift++) //look for a position up right down left
                    {
                        this->getNewCoordinates(shift,offspringX, offspringY);
                        if (newX >= 0 && newX < WORLD_SIZE &&                       //check bounds
                            newY >= 0 && newY < WORLD_SIZE &&
                            this->antSpace[offspringX][offspringY] == nullptr &&    //no ants in [offspringX,offspringY]
                            this->dbSpace[offspringX][offspringY] == nullptr        //no DB in [offspringX,offspringY]
                            )
                        {   //found place.
                            this->antSpace[offspringX][offspringY] = offspring;
                            placed = true;
                            break; //placed the offspring. terminates shift for loop.
                        }
                    }
                    if (!placed)
                    {
                        delete offspring; //no free space for the offspring
                        offspring = nullptr;
                    }
                }
            }
        }
    }
}