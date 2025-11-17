#include "stack.h"

llic_stack_t *llic_stack_new(const size_t size) {
  llic_stack_t *stack = malloc(sizeof(llic_stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->index = 0;
  stack->size = size;

  uint16_t *data = malloc(sizeof(uint16_t) * size);
  if (data == NULL) {
    free(stack); // also free stack if fails
    return NULL;
  }

  stack->data = data;
  return stack;
}

uint8_t llic_stack_push(llic_stack_t *stack, const uint16_t value) {
  if (stack->index >= stack->size)
    return 0;

  stack->data[stack->index++] = value;
  return 1;
}

uint8_t llic_stack_pop(llic_stack_t *stack, uint16_t *out) {
  if (stack->index == 0)
    return 0;

  *out = stack->data[--stack->index];
  return 1;
}

uint8_t llic_stack_swap(const llic_stack_t *stack) {
  if (stack->index < 2)
    return 0;

  const uint16_t temporary = stack->data[stack->index - 1];
  stack->data[stack->index - 1] = stack->data[stack->index - 2];
  stack->data[stack->index - 2] = temporary;

  return 1;
}

uint8_t llic_stack_reverse(llic_stack_t *stack) {
  uint16_t value;
  if (!llic_stack_pop(stack, &value))
    return 0;

  value = !value;
  return llic_stack_push(stack, value);
}

void llic_stack_free(llic_stack_t *stack) {
  free(stack->data);
  free(stack);
}
