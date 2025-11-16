#ifndef LLIC_STACK_H
#define LLIC_STACK_H

#include <stdlib.h>

typedef struct {
  size_t index;
  size_t size;
  uint16_t *data;
} llic_stack_t;

llic_stack_t *llic_stack_new(size_t size);

uint8_t llic_stack_push(llic_stack_t *stack, uint16_t value);

uint8_t llic_stack_pop(llic_stack_t *stack, uint16_t *out);

uint8_t llic_stack_swap(const llic_stack_t *stack);

uint8_t llic_stack_reverse(llic_stack_t *stack);

void llic_stack_free(llic_stack_t *stack);

#endif // LLIC_STACK_H
