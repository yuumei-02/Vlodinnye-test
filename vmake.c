#define VMAKE_IMPL
#include <vmake.h>

Vmake vmake;

bool build() {
   ModuleId mod_1 = Module_new("vtest", "./vtest", MT_Executable);
   return Vmake_build(mod_1, BuildOptions_default_debug());
}

i32 main(i32 argc, cstr argv[]) {
   vmake = Vmake_go_rebuild_yourself(argc, argv);

   cstr_match(argv[1]) {
      ncstreq("build") return build();
      else {
         eprintln("[!] Unknown command \"%s\"", argv[1]);
         return 1;
      }
   }

   return 0;
}


