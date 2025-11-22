#ifndef LLIC_REGISTER_H
#define LLIC_REGISTER_H

#include <stdlib.h>

/// Represents the IDs for the available general-purpose registers.
typedef enum {
  REG_A,
  REG_B,
  REG_C,
  REG_D,
  REG_E,
  /// Register F often used for flags or comparisons.
  REG_F,
  REG_COUNT
} llic_register_id_t;

/// Holds the state of all general-purpose registers.
typedef struct {
  uint16_t a;
  uint16_t b;
  uint16_t c;
  uint16_t d;
  uint16_t e;
  uint16_t f;
} llic_register_t;

/**
 * @brief Creates a register set with all registers initialized to zero.
 *
 * @return A structure with all fields set to 0.
 */
llic_register_t llic_register_default(void);

/**
 * @brief Gets the value from a specific register by its ID.
 *
 * @param registers The register structure to read from.
 * @param id The ID of the register to get.
 * @param out A pointer to store the retrieved 16-bit value.
 *
 * @return Returns 1 on success, or 0 if the register ID is invalid.
 */
uint8_t llic_register_get(llic_register_t registers, llic_register_id_t id,
                          uint16_t *out);

/**
 * @brief Sets the value of a specific register by its ID.
 *
 * @param registers A pointer to the register structure to modify.
 * @param id The ID of the register to set.
 * @param value The 16-bit value to write into the register.
 *
 * @return Returns 1 on success, or 0 if the register ID is invalid.
 */
uint8_t llic_register_set(llic_register_t *registers, llic_register_id_t id,
                          uint16_t value);

#endif // LLIC_REGISTER_H
