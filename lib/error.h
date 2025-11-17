#ifndef LLIC_ERROR_H
#define LLIC_ERROR_H

#include <string.h>

/// Represents all possible runtime error codes.
typedef enum {
  ERROR_NONE = 0,
  ERROR_UNKNOWN_COMMAND,
  ERROR_STACK_OVERFLOW,
  ERROR_STACK_UNDERFLOW,
  ERROR_UNKNOWN_REGISTER,
  ERROR_PERMISSION_DENIED,
  ERROR_MACOS_API,
  ERROR_DIVIDE_BY_ZERO
} llic_error_id_t;

/// Represents a runtime error, containing a descriptive message.
typedef struct {
  llic_error_id_t id;
  /// A fixed-size buffer for a human-readable error message.
  char message[128];
} llic_error_t;

/**
 * @brief Creates a new error structure based on an error ID.
 *
 * @param id The error code to use for the new error.
 *
 * @return An error structure.
 */
llic_error_t llic_error_new(llic_error_id_t id);

#endif // LLIC_ERROR_H
