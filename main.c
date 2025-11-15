#include "lib/config.h"
#include "lib/vm.h"

#include <stdio.h>

int main(void) {
  llic_bytecode_t *bytecode = llic_bytecode_new(32);

  llic_bytecode_append(bytecode, COMMAND_PUSH);
  llic_bytecode_append(bytecode, 0);
  llic_bytecode_append(bytecode, 99);
  llic_bytecode_append(bytecode, COMMAND_POP);
  llic_bytecode_append(bytecode, 0);

  llic_vm_t *vm = llic_vm_new(bytecode, llic_config_default());
  uint8_t res = llic_vm_loop(vm);

  if (res == 0) {
    printf("vm error: %s\n", vm->error.message);
    return 1;
  }

  printf("%d %d %d %d %d %d\n", vm->registers.a, vm->registers.b,
         vm->registers.c, vm->registers.d, vm->registers.e, vm->registers.f);

  return 0;
}