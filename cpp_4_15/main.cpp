/*Now I would like you to do a switch statement with breaks
**between the cases. Create a program that asks the user for
**two float numbers. Then asks the user if they would like to:
**add the numbers, subtract the numbers, multiply the numbers,
**divide the numbers.
**The program should then print the numbers with the chosen
**operation and the solution.
*/

#include <iostream>

int main()
{
    float in1, in2;
    char operation;
    float answer;

    std::cout << "Enter two numbers:\n";
    std::cin >> in1;
    std::cin >> in2;
    std::cout << "Enter the operation '+','-','*','/':\n";
    std::cin >> operation;

    switch (operation)
    {
    case ('+'):
    {
        answer = in1 + in2;
        break;
    }
    case ('-'):
    {
        answer = in1 - in2;
        break;
    }
    case ('*'):
    {
        answer = in1 * in2;
        break;
    }
    case ('/'):
    {
        answer = in1 / in2;
        break;
    }
    default:
        std::cout << "Illegal operation";
    }

    std::cout << in1 << operation << in2 << " = " << answer << "\n";

    return 0;
}