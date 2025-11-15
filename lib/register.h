#ifndef LLIC_REGISTER_H
#define LLIC_REGISTER_H

#include <stdlib.h>

typedef enum {
  REG_A,
  REG_B,
  REG_C,
  REG_D,
  REG_E,
  REG_F,
  REG_COUNT
} llic_register_id_t;

typedef struct {
  uint16_t a;
  uint16_t b;
  uint16_t c;
  uint16_t d;
  uint16_t e;
  uint16_t f;
} llic_register_t;

llic_register_t llic_register_default(void);

uint8_t llic_register_get(llic_register_t registers, llic_register_id_t id,
                          uint16_t *out);

#endif // LLIC_REGISTER_H
