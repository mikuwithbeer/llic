#ifndef LLIC_VM_H
#define LLIC_VM_H

#include "bytecode.h"
#include "command.h"
#include "config.h"
#include "error.h"
#include "input.h"
#include "register.h"
#include "stack.h"

/// Represents the current execution state of the VM.
typedef enum {
  STATE_IDLE = 0,
  STATE_COLLECT,
  STATE_EXECUTE,
  STATE_HALT
} llic_vm_state_t;

/// Represents the complete state of a VM.
typedef struct {
  /// The current position in the bytecode (instruction pointer).
  size_t cursor;
  llic_vm_state_t state;

  llic_bytecode_t *bytecode;
  llic_command_t command;
  llic_config_t config;
  llic_error_t error;
  llic_register_t registers;
  llic_stack_t *stack;
} llic_vm_t;

/**
 * @brief Creates a new VM instance.
 *
 * @param bytecode A pointer to the bytecode to be loaded into the VM.
 * @param config The configuration to apply to this VM instance.
 *
 * @return A pointer to the newly allocated VM, or NULL if allocation fails.
 */
llic_vm_t *llic_vm_new(llic_bytecode_t *bytecode, llic_config_t config);

/**
 * @brief Executes VM's main loop.
 *
 * @param vm A pointer to the VM instance to run.
 *
 * @return Returns 0 if there are any errors.
 */
uint8_t llic_vm_loop(llic_vm_t *vm);

/**
 * @brief Executes the command currently loaded.
 *
 * @param vm A pointer to the VM instance.
 */
void llic_vm_execute(llic_vm_t *vm);

/**
 * @brief Frees all memory associated with the VM instance.
 *
 * @param vm A pointer to the VM instance to be freed.
 */
void llic_vm_free(llic_vm_t *vm);

#endif // LLIC_VM_H
