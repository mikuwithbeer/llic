#include "error.h"

llic_error_t llic_error_new(const llic_error_id_t id) {
  llic_error_t error = {0};
  error.id = id;

  switch (id) {
  case ERROR_NONE:
    break;
  case ERROR_UNKNOWN_COMMAND:
    strcpy(error.message, "Unknown VM command");
    break;
  }

  return error;
}
