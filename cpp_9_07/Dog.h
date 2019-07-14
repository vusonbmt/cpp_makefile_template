
#include<iostream>
#include<string>
using namespace std;

class Dog
{
    private:
        string name;
        int license;
    public:
        Dog();
        Dog(string nameIn);
        Dog(int licIn);
        Dog(string nameIn, int licIn);
        string getName();
        int getLicense();
};

Dog::Dog()
{
    name = "NA";
    license = 0;
}

Dog::Dog(string nameIn)
{
    name = nameIn;
    license = 0;
}

Dog::Dog(int licIn)
{
    name = "NA";
    license = licIn;
}

Dog::Dog(string nameIn, int licIn)
{
    name = nameIn;
    license = licIn;
}

string Dog::getName()
{
    return name;
}

int Dog::getLicense()
{
    return license;
}    