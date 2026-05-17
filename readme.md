# About
Vlodinnye test or vtest for short, is a simple testing library in C for C.

# Dependencies
The project depends the Mektova-C-Utils library which you can find here: https://github.com/yuumei-02/Mektova-C-Utils

# Building
In order to build the project, you must first bootstrap the build system. <br>
This can be done by running the following shell command. <br>
```sh
$ gcc -std=c23 ./vmake.c -o ./vmake -lmcu-debug
```
Now, run ```./vmake build``` to build the project and you're done.

# Example
```C
#define VTEST_IMPL
#include "vtest.h"

TestResult compute() {
   // run test code
   
   // Return either one of the three result types
   switch (result) {
      case 0: return TR_Pass;
      case 1: return TR_Skip;
      case 2: return TR_Fail;
   }
}

i32 main() {
   // Setup test running and set the ui width
   Vtest_start(35);

   // Run a test function either with a custom name or not
   run_test(compute)
   run_test_ex(compute, "compute me!");
   
   // Stop test running and dump the results
   Vtest_end();
   
   // You may call Vtest_start again
   // to start a new test block
   return 0;
}
```

