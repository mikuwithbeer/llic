#ifndef LLIC_BYTECODE_H
#define LLIC_BYTECODE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  size_t length;
  size_t capacity;
  uint8_t *data;
} llic_bytecode_t;

llic_bytecode_t *llic_bytecode_new(size_t capacity);

uint8_t llic_bytecode_get(const llic_bytecode_t *bytecode, size_t index,
                          uint8_t *out);

uint8_t llic_bytecode_append(llic_bytecode_t *bytecode, uint8_t value);

uint8_t llic_bytecode_load(llic_bytecode_t *bytecode, const uint8_t *data,
                           size_t length);

void llic_bytecode_free(llic_bytecode_t *bytecode);

#endif // LLIC_BYTECODE_H
