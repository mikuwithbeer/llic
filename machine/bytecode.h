#ifndef LLIC_BYTECODE_H
#define LLIC_BYTECODE_H

#include <stdint.h>
#include <stdlib.h>

/// Represents bytecode, which is actually a char vector.
typedef struct {
  size_t length;
  size_t capacity;
  uint8_t *data;
} llic_bytecode_t;

/**
 * @brief Creates new bytecode.
 *
 * @param capacity Default capacity might increase internally depending on data.
 *
 * @return Returns bytecode or NULL.
 */
llic_bytecode_t *llic_bytecode_new(size_t capacity);

/**
 * @brief Safely retrieves a byte from the bytecode at a specific index.
 *
 * @param bytecode The bytecode structure to read from.
 * @param index The index of the byte to retrieve.
 * @param out A pointer where the retrieved byte will be stored.
 *
 * @return Returns 1 on success, or 0 if the index is out of bounds.
 */
uint8_t llic_bytecode_get(const llic_bytecode_t *bytecode, size_t index,
                          uint8_t *out);

/**
 * @brief Appends a single byte to the end of the bytecode.
 *
 * @param bytecode The bytecode structure to append to.
 * @param value The 8-bit value to append.
 *
 * @return Returns 1 on success, or 0 if memory allocation fails.
 */
uint8_t llic_bytecode_append(llic_bytecode_t *bytecode, uint8_t value);

/**
 * @brief Loads a block of data into the bytecode.
 *
 * This function will copy the data from the provided buffer into the
 * bytecode's internal data store, resizing if necessary.
 *
 * @param bytecode The bytecode structure to load data into.
 * @param data A pointer to the data buffer to load from.
 * @param length The number of bytes to load from the data buffer.
 *
 * @return Returns 1 on success, or 0 if memory allocation fails.
 */
uint8_t llic_bytecode_load(llic_bytecode_t *bytecode, const uint8_t *data,
                           size_t length);

/**
 * @brief Frees the memory allocated for the bytecode.
 *
 * @param bytecode A pointer to the bytecode structure to be freed.
 */
void llic_bytecode_free(llic_bytecode_t *bytecode);

#endif // LLIC_BYTECODE_H
