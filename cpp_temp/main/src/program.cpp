#include "mod1c1.hpp"
#include "mod1c2.hpp"
#include "mod2c1.hpp"
#include "mod2c2.hpp"
#include "mod3c1.h"
#include "mod3c2.h"
#include "program.hpp"

int main()
{
   mod1c1 m1c1;
   mod1c2 m1c2;
   mod2c1 m2c1;
   mod2c2 m2c2;

   m1c1.foo();
   m1c2.foo();
   m2c1.foo();
   m2c2.foo();
   csub_init();
   csub_init_process();

   program::foo();

   return 0;
}
