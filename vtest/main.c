#define _POSIX_C_SOURCE 200809L
#define VTEST_IMPL
#include "vtest.h"

#include <time.h>
#include <unistd.h>

TestResult compute() {
   struct timespec delay = {
      .tv_sec = 0,
      .tv_nsec = rand() / 10.0f
   };

   nanosleep(&delay, null);

   i32 result = rand() % 3;
   switch (result) {
      case 0:  return TR_Pass;
      case 1:  return TR_Skip;
      default: return TR_Fail;
   }
}

i32 main() {
   srand(time(null));

   Vtest_start(35);
   for (u32 i = 0; i < 50; ++i) {
      run_test(compute, "compute");
   }
   Vtest_end();
   return 0;
}

