#include "input.h"

uint8_t llic_input_get_mouse_position(uint16_t *x, uint16_t *y) {
  const CGEventRef event = CGEventCreate(NULL);
  if (!event) {
    return 0;
  }

  const CGPoint cursor = CGEventGetLocation(event);
  CFRelease(event);

  *x = (uint16_t)cursor.x;
  *y = (uint16_t)cursor.y;

  return 1;
}

uint8_t llic_input_set_mouse_position(const uint16_t x, const uint16_t y) {
  const CGPoint point = CGPointMake(x, y);
  CGWarpMouseCursorPosition(point);
  CGAssociateMouseAndMouseCursorPosition(true);

  return 1;
}
