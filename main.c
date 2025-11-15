#include "lib/config.h"
#include "lib/vm.h"

#include <stdio.h>

int main(void) {
  llic_bytecode_t *bytecode = llic_bytecode_new(32);

  llic_bytecode_append(bytecode, COMMAND_PUSH);
  llic_bytecode_append(bytecode, 0);
  llic_bytecode_append(bytecode, 99);
  llic_bytecode_append(bytecode, COMMAND_PUSH);
  llic_bytecode_append(bytecode, 10);
  llic_bytecode_append(bytecode, 2);
  llic_bytecode_append(bytecode, COMMAND_SWAP);
  llic_bytecode_append(bytecode, COMMAND_SET_REGISTER);
  llic_bytecode_append(bytecode, 2);
  llic_bytecode_append(bytecode, 20);
  llic_bytecode_append(bytecode, 40);
  llic_bytecode_append(bytecode, COMMAND_GET_REGISTER);
  llic_bytecode_append(bytecode, 2);

  llic_vm_t *vm = llic_vm_new(bytecode, llic_config_default());
  uint8_t res = llic_vm_loop(vm);

  if (res == 0) {
    printf("vm error: %s\n", vm->error.message);
    return 1;
  }

  printf("(a..f): %d %d %d %d %d %d\n", vm->registers.a, vm->registers.b,
         vm->registers.c, vm->registers.d, vm->registers.e, vm->registers.f);

  printf("stack: %d %d %d\n", vm->stack->data[0], vm->stack->data[1],
         vm->stack->data[2]);

  return 0;
}