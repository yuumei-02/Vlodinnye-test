#define _POSIX_C_SOURCE 200809L
#define VTEST_IMPL
#include "vtest.h"

#include <time.h>
#include <unistd.h>

TestResult compute(TestResult previous) {
   if (previous == TR_Pass) return TR_Skip;

   struct timespec delay = {
      .tv_sec = 0,
      .tv_nsec = rand() / 10.0f
   };

   nanosleep(&delay, null);

   i32 result = rand() % 2;
   switch (result) {
      case 0:  return TR_Pass;
      default: return TR_Fail;
   }
}

i32 main() {
   srand(time(null));

   Vtest_start(35);
   TestResult result = TR_Unknown;
   for (u32 i = 0; i < 20; ++i) {
      result = run_test_ex(compute, "first", result);
      result = run_test_ex(compute, "second", result);
      result = run_test(compute);
   }
   Vtest_end();
   return 0;
}

