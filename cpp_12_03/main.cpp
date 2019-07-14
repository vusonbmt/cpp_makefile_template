/*
*/
#include "main.h"

int main()
{
    const string status = "salary"; //options: hourly or salary
    string level;
    
    //assign an manager to e1
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

    cout<<"e1 pay: $"<<e1->calcWeeklyPay();
    
    //assign an employee to e2
    level = "hourly";
    Employee *e2; //e1 is now a pointer to Employee object
    
    if(status != level)
    {
        e2 = new Employee(); //we define an hourly employee
    }
    else
    {
        e2 = new Manager(); //we define a salaried employee
    }  
    
    e2->setPayRate(10.00);
    cout<<"\ne2 pay: $"<<e2->calcWeeklyPay() << "\n";
    
    return 0;
}