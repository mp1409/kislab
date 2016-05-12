/**
 * \file
 *
 * Base definitions.
 */
const int PHOTO_SENSOR = 2;
const int HALL_SENSOR = 3;
const int TRIGGER_PIN = 4;
const int SWITCH = 5;
const int SERVO_PIN = 9;
const int YELLOW_LED = 12;
const int GREEN_LED = 13;

const int SERVO_CLOSED = 0;
const int SERVO_OPEN = 20;

template<int x, int y>
struct add{
  enum {
    value = x + y
  };
};