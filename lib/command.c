#include "command.h"

uint8_t llic_command_to_argc(const llic_command_id_t id) {
  switch (id) {
  case COMMAND_NOP:
  case COMMAND_SWAP_STACK:
  case COMMAND_REVERSE_STACK:
  case COMMAND_GET_MOUSE_POSITION:
  case COMMAND_SET_MOUSE_POSITION:
  case COMMAND_EXECUTE_MOUSE:
  case COMMAND_SCROLL_MOUSE:
  case COMMAND_SLEEP:
  case COMMAND_HALT:
  case COMMAND_EXECUTE_KEYBOARD:
    return 0;
  case COMMAND_POP_STACK:
  case COMMAND_GET_REGISTER:
  case COMMAND_JUMP_BACK:
  case COMMAND_JUMP_FORWARD:
    return 1;
  case COMMAND_PUSH_STACK:
  case COMMAND_COPY_REGISTER:
  case COMMAND_ADD_REGISTER:
  case COMMAND_SUB_REGISTER:
  case COMMAND_MUL_REGISTER:
  case COMMAND_DIV_REGISTER:
  case COMMAND_MOD_REGISTER:
  case COMMAND_BIGGER_REGISTER:
  case COMMAND_SMALLER_REGISTER:
  case COMMAND_EQUAL_REGISTER:
    return 2;
  case COMMAND_SET_REGISTER:
    return 3;
  }

  return UNREACHABLE_ARGC;
}

llic_permission_t llic_permission_from_command(llic_command_id_t id) {
  switch (id) {
  case COMMAND_GET_MOUSE_POSITION:
  case COMMAND_SET_MOUSE_POSITION:
  case COMMAND_EXECUTE_MOUSE:
  case COMMAND_SCROLL_MOUSE:
    return PERM_MOUSE;
  case COMMAND_EXECUTE_KEYBOARD:
    return PERM_KEYBOARD;
  case COMMAND_SLEEP:
    return PERM_OS;
  default:
    return PERM_NONE;
  }
}
