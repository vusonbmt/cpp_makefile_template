/*Goal: practice if-else statements in C++
**Write a program to select the best pet.
*/

#include <iostream>

int main()
{
    char skin, location;
    std::cout << "Would you like an animal with fur(f), feathers(t), or scales(s)?";
    std::cin >> skin;
    std::cout << skin << "\n";

    //Use if-else statements to control program flow
    if (skin == 'f')
    {
        std::cout << "Get a dog"
                  << "\n";
    }
    else if (skin == 't')
    {
        std::cout << "Get a bird"
                  << "\n";
    }
    else if (skin == 's')
    {
        std::cout << "Would you like an animal that lives in water(w), land(l), or both(b)?";
        std::cin >> location;
        std::cout << location << "\n";

        //Use if-else statements to control program flow
        //note that the curly braces are not necessary if there is only
        //one line of code.

        if (location == 'w')
            std::cout << "Get a fish"
                      << "\n";
        else if (location == 'l')
            std::cout << "Get a gecko"
                      << "\n";
        else if (location == 'b')
            std::cout << "Get a frog"
                      << "\n";
        else
            std::cout << "Enter water(w), land(l), or both(b)\n";
    }
    else
        std::cout << "Please choose fur(f), feathers(t), scales(s)"
                  << "\n";
    return 0;
}