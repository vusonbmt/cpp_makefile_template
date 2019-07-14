
#include <iostream>
#include <string>
using namespace std;

class Flower
{
    private:
        string bloomTime;
    public:
        Flower();
        void setBloomTime(string bloomIn);
        string getBloomTime();
};

Flower::Flower()
{
    bloomTime = "NA";
}

void Flower::setBloomTime(string bloomIn)
{
    bloomTime = bloomIn;
}

string Flower::getBloomTime()
{
    return bloomTime;
}

class Rose : public Flower
{
    private:
        string fragrance;
    public:
        Rose();
        void setFragrance(string fragIn);
        string getFragrance();
};

Rose::Rose()
{
    fragrance = "NA";
}

void Rose::setFragrance(string fragIn)
{
    fragrance = fragIn;
}

string Rose::getFragrance()
{
    return fragrance;
}