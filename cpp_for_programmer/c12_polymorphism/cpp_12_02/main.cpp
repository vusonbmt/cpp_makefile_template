/*Goal: understand virtual functions
*In main.hpp we added the keyword 
*virtual to the function calcWeeklyPay.
*Does this fix the problem?
*/

#include "main.h"

int main()
{
    const string status = "salary"; //options: hourly or salary
    string level;
    level = "salary";
    Employee *e1; //e1 is now a pointer to Employee object
    
    if(status != level)
    {
        e1 = new Employee(); //we define an hourly employee
    }
    else
    {
        e1 = new Manager(); //we define a salaried employee
    }  
    
    e1->setPayRate(12000.00);
    cout<<"It works!\n";
    cout<<"e1 pay: $"<<e1->calcWeeklyPay();
    delete e1;
    return 0;
}