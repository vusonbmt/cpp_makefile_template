/*Goal: practice using the Dogs class. 
**Create an array called roster whose elements are of the type Dogs.
*/

#include "main.h"


int main()
{
    const int SIZE=3;
    Dog roster[SIZE];

    roster[0].setName("Blue");
    roster[1].setName("King");
    roster[2].setName("Spot");

    printRoster(roster,SIZE);
    return 0;
}

