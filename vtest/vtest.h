#ifndef VTEST_H
#define VTEST_H

#include <mcu/core.h>
#include <mcu/io.h>

typedef enum {
   TR_Pass,
   TR_Fail,
   TR_Skip
} TestResult;

typedef TestResult (*TestFn)();

typedef struct {
   u32 passes;
   u32 fails;
   u32 skips;

   u32 ui_width;
} TestState;

void Vtest_start(u32 ui_width);
void Vtest_end();

#define run_test(test_fn) \
   run_test_ex(test_fn, #test_fn)

TestResult run_test_ex(TestFn test_fn, const cstr const name);

extern TestState state;

#endif

#ifdef VTEST_IMPL
#undef VTEST_IMPL

#include <mcu/handlers.h>

TestState state = {0};

static const cstr reset  = "\x1b[0m";
static const cstr red    = "\x1b[31m";
static const cstr yellow = "\x1b[33m";
static const cstr green  = "\x1b[32m";
static const cstr blue   = "\x1b[34m";

void repeat_puts(const cstr const str, u32 count) {
   for (u32 i = 0; i < count; ++i) {
      printf(str);
   }
}

void Vtest_start(u32 ui_width) {
   state = (TestState) {
      .ui_width = ui_width
   };

   printf("┌");
   repeat_puts("─", state.ui_width);
   printf("┐\n");
}

void Vtest_end() {
   printf("├");
   repeat_puts("─", state.ui_width);
   printf("┤\n");

   repeat_puts(" ", state.ui_width + 1);
   printf("│\r");
   printf("│Total  : [%s%u%s]\n", blue, state.passes + state.skips + state.fails, reset);
   
   repeat_puts(" ", state.ui_width + 1);
   printf("│\r");
   printf("│Result : [%s%u%s/%s%u%s/%s%u%s]\n",
      green,  state.passes, reset,
      yellow, state.skips,  reset,
      red,    state.fails,  reset);

   repeat_puts(" ", state.ui_width + 1);
   printf("│\r");
   printf("│Format : %spasses%s, %sskips%s, %sfails%s\n",
      green,  reset,
      yellow, reset,
      red,    reset);
   
   printf("└");
   repeat_puts("─", state.ui_width);
   printf("┘\n");
}

TestResult run_test_ex(TestFn test_fn, const cstr const name) {
   mcu_assert(test_fn != nullptr, "test_fn can't be null");

   repeat_puts(" ", state.ui_width + 1);
   printf("│\r");
   printf("│%s[%s]...%s\r", blue, name, reset);

   TestResult result = test_fn();
   
   switch (result) {
      case TR_Pass: {
         state.passes += 1;
         printf("│%s[%s] passed%s\n", green, name, reset);
      } return result;

      case TR_Skip: {
         state.skips  += 1;
         printf("│%s[%s] skip%s\n", yellow, name, reset);
      } return result;
      
      case TR_Fail: {
         state.fails  += 1;
         printf("│%s[%s] failed%s\n", red, name, reset);
      } return result;
   }

   panic("test_fn returned an invalid TestResult enum variant");
}

#endif

