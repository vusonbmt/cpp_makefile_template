#include <iostream>

/*The function declaration can be omitted in the header file.
 **As long as the function is defined before it is used,
 **the declaration is optional.
**It is often considered good practice to list the declarations
**at the top of the header file.
*/
void printProduct(int m1, int m2, int product);

void printProduct(int m1, int m2, int product)
{
    std::cout << m1 << "*" << m2 << " = " << product << " \n";
}