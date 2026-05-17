#define VMAKE_IMPL
#include <vmake.h>

Vmake vmake;

i32 build() {
   ModuleId mod_1 = Module_new("vtest", "./vtest", MT_Executable);
   return Vmake_build(mod_1, BuildOptions_default_debug());
}

i32 install() {
   return execute_command("sudo cp ./vtest/vtest.h /usr/local/include/vtest.h");
}

i32 main(i32 argc, cstr argv[]) {
   vmake = Vmake_go_rebuild_yourself(argc, argv);

   cstr_match(argv[1]) {
      ncstreq("build")  return build();
      cstreq("install") return install();
      else {
         eprintln("[!] Unknown command \"%s\"", argv[1]);
         return 1;
      }
   }

   return 0;
}


