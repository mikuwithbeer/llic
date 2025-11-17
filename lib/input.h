#ifndef LLIC_INPUT_H
#define LLIC_INPUT_H

#include <ApplicationServices/ApplicationServices.h>

/**
 * @brief Gets the current global mouse cursor position.
 *
 * @param x A pointer to store X coordinate.
 * @param y A pointer to store Y coordinate.
 *
 * @return Returns 1 on success, or 0 if the position could not be retrieved.
 */
uint8_t llic_input_get_mouse_position(uint16_t *x, uint16_t *y);

/**
 * @brief Sets the global mouse cursor position.
 *
 * @param x The X coordinate to move the mouse to.
 * @param y The Y coordinate to move the mouse to.
 *
 * @return Returns 1 on success, or 0 if the position could not be set.
 */
uint8_t llic_input_set_mouse_position(uint16_t x, uint16_t y);

#endif // LLIC_INPUT_H
