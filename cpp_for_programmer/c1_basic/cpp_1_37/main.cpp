/*Goal: practice std::cin for strings
**Write a program that prompts two user2 for their
**name, address, and phone number.
**Print the information to the console in the following format:
**name
**\/t\/t address
**\/t\/tphone number
*/

#include <iostream>
#include <string>

int main()
{
    std::string name1, address1, phoneNo1;
    std::string name2, address2, phoneNo2;

    //get user1 information
    std::cout << "User1 what is your name?\n";
    std::getline(std::cin, name1);
    std::cout << "User1 what is your address?\n";
    std::getline(std::cin, address1);
    std::cout << "User1 what is your phone number?\n";
    std::getline(std::cin, phoneNo1);

    //get user2 information
    std::cout << "User2 what is your name?\n";
    std::getline(std::cin, name2);
    std::cout << "User2 what is your address?\n";
    std::getline(std::cin, address2);
    std::cout << "User2 what is your phone number?\n";
    std::getline(std::cin, phoneNo2);

    //print information
    std::cout << "\n\n"
              << name1 << "\n";
    std::cout << "\t\t" << address1 << "\n";
    std::cout << "\t\t" << phoneNo1 << "\n";

    std::cout << "\n\n"
              << name2 << "\n";
    std::cout << "\t\t" << address2 << "\n";
    std::cout << "\t\t" << phoneNo2 << "\n";
    return 0;
}