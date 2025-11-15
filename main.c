#include "lib/config.h"
#include "lib/vm.h"

#include <stdio.h>

int main(void) {
  llic_bytecode_t *bytecode = llic_bytecode_new(32);

  llic_bytecode_append(bytecode, 92);
  llic_bytecode_append(bytecode, 3);
  llic_bytecode_append(bytecode, 10);
  llic_bytecode_append(bytecode, COMMAND_NOP);
  llic_bytecode_append(bytecode, 31);
  llic_bytecode_append(bytecode, 69);

  llic_vm_t *vm = llic_vm_new(bytecode, llic_config_default());
  uint8_t res = llic_vm_run(vm);

  if (res == 0) {
    printf("Error: %s\n", vm->error.message);
    return 1;
  }

  return 0;
}