#ifndef LLIC_INPUT_H
#define LLIC_INPUT_H

#include <ApplicationServices/ApplicationServices.h>

uint8_t llic_input_get_mouse_position(uint16_t *x, uint16_t *y);
uint8_t llic_input_set_mouse_position(uint16_t x, uint16_t y);

#endif // LLIC_INPUT_H
