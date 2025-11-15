#include "vm.h"

llic_vm_t *llic_vm_new(llic_bytecode_t *bytecode, const llic_config_t config) {
  if (bytecode == NULL)
    return NULL;

  llic_vm_t *vm = malloc(sizeof(llic_vm_t));
  if (vm == NULL)
    return NULL;

  vm->cursor = 0;
  vm->state = STATE_IDLE;

  vm->bytecode = bytecode;
  vm->command = (llic_command_t){0};
  vm->config = config;
  vm->error = (llic_error_t){0};

  vm->stack = llic_stack_new(config.stack_capacity);
  if (vm->stack == NULL) {
    free(vm);
    return NULL;
  }

  return vm;
}

uint8_t llic_vm_loop(llic_vm_t *vm) {
  uint8_t argi = 0, argc = 0;
  llic_bytecode_append(vm->bytecode, COMMAND_NOP); // bug

  while (vm->cursor < vm->bytecode->length) {
    if (vm->state == STATE_EXECUTE) {
      llic_vm_execute(vm);
      vm->state = STATE_IDLE;
    } else if (vm->error.id != ERROR_NONE) {
      return 0;
    } else {
      uint8_t byte;
      llic_bytecode_get(vm->bytecode, vm->cursor++, &byte);

      switch (vm->state) {
      case STATE_IDLE: {
        const llic_command_id_t cid = (llic_command_id_t)byte;
        vm->command.id = cid;

        argi = 0, argc = llic_command_to_argc(cid);
        if (argc == 0) {
          vm->state = STATE_EXECUTE;
        } else if (argc == UNREACHABLE_ARGC) {
          vm->error = llic_error_new(ERROR_UNKNOWN_COMMAND);
        } else {
          vm->state = STATE_COLLECT;
        }

        break;
      }

      case STATE_COLLECT: {
        vm->command.args[argi++] = byte;
        if (argi == argc) {
          vm->state = STATE_EXECUTE;
        }

        break;
      }
      default:
        break;
      }
    }
  }

  return 1;
}

void llic_vm_execute(llic_vm_t *vm) {
  llic_command_t command = vm->command;
  switch (command.id) {
  case COMMAND_NOP: {
    break;
  }
  case COMMAND_PUSH: {
    const uint16_t value = (command.args[0] << 8) | (command.args[1] << 0);
    if (!llic_stack_push(vm->stack, value)) {
      vm->error = llic_error_new(ERROR_STACK_OVERFLOW);
    }

    break;
  }
  case COMMAND_POP: {
    uint16_t value;
    const llic_register_id_t rid = (llic_register_id_t)command.args[0];
    if (!llic_stack_pop(vm->stack, &value)) {
      vm->error = llic_error_new(ERROR_STACK_UNDERFLOW);
      return;
    }

    if (!llic_register_set(&vm->registers, rid, value))
      vm->error = llic_error_new(ERROR_UNKNOWN_REGISTER);

    break;
  }
  case COMMAND_SWAP: {
    if (!llic_stack_swap(vm->stack)) {
      vm->error = llic_error_new(ERROR_STACK_UNDERFLOW);
    }

    break;
  }
  }
}

void llic_vm_free(llic_vm_t *vm) {
  llic_stack_free(vm->stack);
  llic_bytecode_free(vm->bytecode);
  free(vm);
}
