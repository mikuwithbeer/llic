#include "vm.h"

/* ==========================================
 * SOME INTERNAL FUNCTIONS TO AVOID REPEATING
 * ==========================================
 */

static uint8_t vm_stack_push(llic_vm_t *vm, const uint16_t value) {
  if (!llic_stack_push(vm->stack, value)) {
    vm->error = llic_error_new(ERROR_STACK_OVERFLOW);
    return 0;
  }

  return 1;
}

static uint8_t vm_stack_pop(llic_vm_t *vm, uint16_t *value) {
  if (!llic_stack_pop(vm->stack, value)) {
    vm->error = llic_error_new(ERROR_STACK_UNDERFLOW);
    return 0;
  }

  return 1;
}

static uint8_t vm_get_register(llic_vm_t *vm, const llic_register_id_t rid,
                               uint16_t *value) {
  if (!llic_register_get(vm->registers, rid, value)) {
    vm->error = llic_error_new(ERROR_UNKNOWN_REGISTER);
    return 0;
  }

  return 1;
}

static uint8_t vm_set_register(llic_vm_t *vm, const llic_register_id_t rid,
                               const uint16_t value) {
  if (!llic_register_set(&vm->registers, rid, value)) {
    vm->error = llic_error_new(ERROR_UNKNOWN_REGISTER);
    return 0;
  }

  return 1;
}

static uint8_t vm_get_two_register(llic_vm_t *vm, const llic_register_id_t rid1,
                                   const llic_register_id_t rid2,
                                   uint16_t *value1, uint16_t *value2) {
  if (!llic_register_get(vm->registers, rid1, value1) ||
      !llic_register_get(vm->registers, rid2, value2)) {
    vm->error = llic_error_new(ERROR_UNKNOWN_REGISTER);
    return 0;
  }

  return 1;
}

/* ==========================
 * ACTUALLY EXPOSED FUNCTIONS
 * ==========================
 */

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
    free(vm); // also free vm
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

      if (vm->state == STATE_EXECUTE)
        vm->state = STATE_IDLE;
    } else if (vm->error.id != ERROR_NONE) {
      // error is already stored inside vm
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
      case STATE_HALT: {
        return 1;
      }
      default:
        break;
      }
    }
  }

  return 1;
}

void llic_vm_execute(llic_vm_t *vm) {
  const llic_command_t cmd = vm->command;
  const llic_permission_t cmd_perm = llic_permission_from_command(cmd.id);

  if (!llic_config_check(vm->config, cmd_perm)) {
    vm->error = llic_error_new(ERROR_PERMISSION_DENIED);
    return;
  }

  // these variables can be shared since they are used in most of the opcodes
  uint16_t value, value2;
  llic_register_id_t rid, rid2;

  switch (cmd.id) {
  case COMMAND_NOP: {
    break;
  }
  case COMMAND_JUMP_BACK: {
    rid = (llic_register_id_t)cmd.args[0];
    if (!vm_get_register(vm, rid, &value))
      return;

    vm->cursor -= value + 1;
    break;
  }
  case COMMAND_JUMP_FORWARD: {
    rid = (llic_register_id_t)cmd.args[0];
    if (!vm_get_register(vm, rid, &value))
      return;

    vm->cursor += value - 1;
    break;
  }
  case COMMAND_HALT: {
    vm->state = STATE_HALT;
    break;
  }
  case COMMAND_PUSH_STACK: {
    value = (cmd.args[0] << 8) | (cmd.args[1] << 0);
    vm_stack_push(vm, value);
    break;
  }
  case COMMAND_POP_STACK: {
    rid = (llic_register_id_t)cmd.args[0];
    if (!vm_stack_pop(vm, &value))
      return;

    vm_set_register(vm, rid, value);
    break;
  }
  case COMMAND_SWAP_STACK: {
    if (!llic_stack_swap(vm->stack))
      vm->error = llic_error_new(ERROR_STACK_UNDERFLOW);

    break;
  }
  case COMMAND_REVERSE_STACK: {
    if (!llic_stack_reverse(vm->stack))
      vm->error = llic_error_new(ERROR_STACK_UNDERFLOW);

    break;
  }
  case COMMAND_SET_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    value = (cmd.args[1] << 8) | (cmd.args[2] << 0);

    vm_set_register(vm, rid, value);
    break;
  }
  case COMMAND_GET_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    if (!vm_get_register(vm, rid, &value))
      return;

    vm_stack_push(vm, value);
    break;
  }
  case COMMAND_COPY_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_register(vm, rid2, &value))
      return;

    vm_set_register(vm, rid, value);
    break;
  }
  case COMMAND_ADD_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    vm_set_register(vm, rid, value + value2);
    break;
  }
  case COMMAND_SUB_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    vm_set_register(vm, rid, value - value2);
    break;
  }
  case COMMAND_MUL_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    vm_set_register(vm, rid, value * value2);
    break;
  }
  case COMMAND_DIV_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    if (value2 == 0) {
      vm->error = llic_error_new(ERROR_DIVIDE_BY_ZERO);
      return;
    }

    vm_set_register(vm, rid, value / value2);
    break;
  }
  case COMMAND_MOD_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    if (value2 == 0) {
      vm->error = llic_error_new(ERROR_DIVIDE_BY_ZERO);
      return;
    }

    vm_set_register(vm, rid, value % value2);
    break;
  }
  case COMMAND_BIGGER_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    vm_stack_push(vm, value > value2);
    break;
  }
  case COMMAND_SMALLER_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    vm_stack_push(vm, value < value2);
    break;
  }
  case COMMAND_EQUAL_REGISTER: {
    rid = (llic_register_id_t)cmd.args[0];
    rid2 = (llic_register_id_t)cmd.args[1];

    if (!vm_get_two_register(vm, rid, rid2, &value, &value2))
      return;

    vm_stack_push(vm, value == value2);
    break;
  }
  case COMMAND_GET_MOUSE_POSITION: {
    uint16_t mouse_x, mouse_y;
    rid = REG_A, rid2 = REG_B;

    if (!llic_input_get_mouse_position(&mouse_x, &mouse_y)) {
      vm->error = llic_error_new(ERROR_MACOS_API);
      return;
    }

    vm_set_register(vm, rid, mouse_x);
    vm_set_register(vm, rid2, mouse_y);
    break;
  }
  case COMMAND_SET_MOUSE_POSITION: {
    uint16_t mouse_x, mouse_y;
    rid = REG_A, rid2 = REG_B;

    if (!vm_get_two_register(vm, rid, rid2, &mouse_x, &mouse_y))
      return;

    llic_input_set_mouse_position(mouse_x, mouse_y);
    break;
  }
  case COMMAND_EXECUTE_MOUSE: {
    uint16_t type;
    rid = REG_A;

    if (!vm_get_register(vm, rid, &type))
      return;

    if (!llic_input_apply_mouse_event(type))
      vm->error = llic_error_new(ERROR_MACOS_API);

    break;
  }
  case COMMAND_SCROLL_MOUSE: {
    uint16_t type, power;
    rid = REG_A, rid2 = REG_B;

    if (!vm_get_two_register(vm, rid, rid2, &type, &power))
      return;

    if (!llic_input_scroll_mouse(power, type))
      vm->error = llic_error_new(ERROR_MACOS_API);

    break;
  }
  case COMMAND_SLEEP: {
    uint16_t ms;
    rid = REG_A;

    if (!vm_get_register(vm, rid, &ms))
      return;

    usleep(ms * 1000);
    break;
  }
  }
}

void llic_vm_free(llic_vm_t *vm) {
  llic_stack_free(vm->stack);
  llic_bytecode_free(vm->bytecode);
  free(vm);
}
