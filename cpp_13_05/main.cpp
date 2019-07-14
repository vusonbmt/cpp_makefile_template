// Goal: pracitce constructing vectors
// and their iterators
// Call the vector vFloat
// Call the iterator it

//TODO: Add the necessary libraries
#include "main.h"

int main()
{
    //TODO: create a vector of floats
    vector<float> vFloat;

    std::cout << "vFloat has " << vFloat.size() << " elements\n";

    //TODO: add elements to the library

    std::cout << "\n\nAdding 10 elements to the vector\n";

    //TODO: assign the value 8.8 to 10 elements of the vector
    vFloat.assign(10, 8.8);
    std::cout << "vFloat has " << vFloat.size() << " elements\n";

    //TODO: Complete the Print function in main.hpp
    // Call the function here to print out each element of vFloat
    printVector(vFloat);

    return 0;
}
