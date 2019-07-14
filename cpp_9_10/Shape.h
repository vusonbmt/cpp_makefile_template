#include <iostream>

using namespace std;

class Shape 
{
    private:
      int length;     // Length of a box
      int width;

    public:
      // Constructor definition
      Shape(int l = 2, int w = 2) 
      {
         length = l;
         width = w;
      }

      int getWidth()
      {
        return width;
      }

      int getLength()
      {
        return length;
      }

      double Area() 
      {
         return length * width;
      }

      int operator +(Shape shapeIn)
      {
          return ((width + shapeIn.getWidth())*(length + shapeIn.getLength()));
      }
};
