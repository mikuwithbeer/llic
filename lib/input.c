#include "input.h"

uint8_t llic_input_get_mouse_position(uint16_t *x, uint16_t *y) {
  const CGEventRef event = CGEventCreate(NULL);
  if (!event)
    return 0;

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

uint8_t llic_input_apply_mouse_event(const uint16_t x, const uint16_t y,
                                     const llic_input_mouse_event_t mei) {
  CGEventType event_type;

  switch (mei) {
  case MOUSE_LEFT_CLICK_DOWN:
    event_type = kCGEventLeftMouseDown;
    break;
  case MOUSE_LEFT_CLICK_UP:
    event_type = kCGEventLeftMouseUp;
    break;
  case MOUSE_RIGHT_CLICK_DOWN:
    event_type = kCGEventRightMouseDown;
    break;
  case MOUSE_RIGHT_CLICK_UP:
    event_type = kCGEventRightMouseUp;
    break;
  default:
    return 0;
  }

  const CGPoint point = CGPointMake(x, y);
  const CGEventRef event = CGEventCreateMouseEvent(NULL, event_type, point, 0);

  CGEventPost(kCGHIDEventTap, event);
  CFRelease(event);

  return 1;
}