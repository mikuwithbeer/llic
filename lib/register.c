#include "register.h"

llic_register_t llic_register_default(void) { return (llic_register_t){0}; }

uint8_t llic_register_get(const llic_register_t registers,
                          const llic_register_id_t id, uint16_t *out) {
  switch (id) {
  case REG_A:
    *out = registers.a;
    break;
  case REG_B:
    *out = registers.b;
    break;
  case REG_C:
    *out = registers.c;
    break;
  case REG_D:
    *out = registers.d;
    break;
  case REG_E:
    *out = registers.e;
    break;
  case REG_F:
    *out = registers.f;
    break;
  default:
    return 0;
  }

  return 1;
}
