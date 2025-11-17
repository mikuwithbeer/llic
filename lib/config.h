#ifndef LLIC_CONFIG_H
#define LLIC_CONFIG_H

#include <stdlib.h>

/// Represents permission flags for controlling VM capabilities.
typedef enum {
  PERM_NONE = 0,
  PERM_MOUSE = 1,
  PERM_KEYBOARD = 2,
  PERM_SCREEN = 4,
  PERM_ALL = PERM_MOUSE | PERM_KEYBOARD | PERM_SCREEN
} llic_permission_t;

/// Holds the configuration settings for a VM instance.
typedef struct {
  uint8_t debug;
  size_t stack_capacity;
  llic_permission_t permission;
} llic_config_t;

/**
 * @brief Creates a default configuration structure.
 *
 * @return Structure with default values.
 */
llic_config_t llic_config_default(void);

/**
 * @brief Checks if the configuration has a specific permission.
 *
 * @param config The configuration to check.
 * @param permission The permission flag(s) to test for.
 *
 * @return Returns 1 if all requested permissions are granted, 0 otherwise.
 */
uint8_t llic_config_check(llic_config_t config, llic_permission_t permission);

#endif // LLIC_CONFIG_H
