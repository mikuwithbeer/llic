#ifndef LLIC_STACK_H
#define LLIC_STACK_H

#include <stdlib.h>

/// Represents a stack for 16-bit values.
typedef struct {
  size_t index;
  size_t size;
  uint16_t *data;
} llic_stack_t;

/**
 * @brief Creates a new, empty stack with a specified capacity.
 *
 * @param size The maximum number of 16-bit values the stack can hold.
 *
 * @return Allocated stack, or NULL if allocation fails.
 */
llic_stack_t *llic_stack_new(size_t size);

/**
 * @brief Pushes a 16-bit value onto the top of the stack.
 *
 * @param stack A pointer to the stack to modify.
 * @param value The value to push.
 *
 * @return Returns 1 on success, or 0 if the stack is full.
 */
uint8_t llic_stack_push(llic_stack_t *stack, uint16_t value);

/**
 * @brief Pops a 16-bit value from the top of the stack.
 *
 * @param stack A pointer to the stack to modify.
 * @param out A pointer to store the popped value.
 *
 * @return Returns 1 on success, or 0 if the stack is empty.
 */
uint8_t llic_stack_pop(llic_stack_t *stack, uint16_t *out);

/**
 * @brief Swaps the top two values on the stack.
 *
 * @param stack A pointer to the stack to modify.
 *
 * @return Returns 1 on success, or 0 if there are less than 2 items.
 */
uint8_t llic_stack_swap(const llic_stack_t *stack);

/**
 * @brief Reverses the top value as boolean.
 *
 * @param stack A pointer to the stack to modify.
 *
 * @return Returns 1 on success, or 0 if there are not any items.
 */
uint8_t llic_stack_reverse(llic_stack_t *stack);

/**
 * @brief Frees the memory allocated for the stack.
 *
 * @param stack A pointer to the stack structure to be freed.
 */
void llic_stack_free(llic_stack_t *stack);

#endif // LLIC_STACK_H
