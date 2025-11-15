#include "command.h"

uint8_t llic_command_to_argc(const llic_command_id_t id) {
  switch (id) {
  case COMMAND_NOP:
    return 0;
  case COMMAND_POP:
    return 1;
  case COMMAND_PUSH:
    return 2;
  default:
    return UNREACHABLE_ARGC;
  }
}
