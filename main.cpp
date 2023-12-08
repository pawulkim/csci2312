
#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;
#include "World.h"
int iterativeSimulation();
int fixedSimulation();

int main()
{
    int type{0};
    cout << "1) Iterative Simulation\n";
    cout << "2) Fixed-Step Simulation\n";
    cout << "Select [1/2]> ";
    cin >> type;

    switch (type)
    {
    case 1:
        return iterativeSimulation();

    case 2:
        return fixedSimulation();

    default:
        cout<< "Invalid Option. Goodbye!\n";
        return 1;
    }
}


int iterativeSimulation()
{
    World* world = new World();
    cout << *world;

    char option='Y';
    cout << "Simulate Step [y/n]? ";
    cin >> option;
    while (option =='y' || option =='Y')
    {
        world->simulate();
        cout << *world;
        cout << "Simulate Step [y/n]? ";
        cin >> option;
    }
    delete world;
    return 0;
}

int fixedSimulation()
{
    World* world = new World();


    int steps{0};
    cout << "Enter Number of Steps> ";
    cin >> steps;

    for (int step{0}; step < steps; step++)
    {
        cout << "++++++ STEP No. " << step << endl;
        cout << *world;
        world->simulate();
    }
    cout << "=======================\n"
         << "===    END WORLD    ===\n"
         << "=======================\n";

    cout << *world;

    delete world;
    return 0;
}