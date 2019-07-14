/*Goal: practice class inheritance
*/

#include "main.h"

int main()
{
    Rose r1;
    r1.setBloomTime("spring");
    r1.setFragrance("strong");
    
    cout<<"r1 blooms in "<<r1.getBloomTime()<<", "<<r1.getFragrance() << "\n";
    return 0;
}