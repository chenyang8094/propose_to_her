#include <wiringPi.h>
#include "beep.h"

namespace sensor
{
void beep_init()
{
    pinMode(BEEP_PIN, OUTPUT);
}
void beep_on()
{
    digitalWrite(BEEP_PIN, LOW);
}
void beep_off()
{
    digitalWrite(BEEP_PIN, HIGH);
}
void beep_toggle()
{
    beep_on();
    beep_off();
}
} // namespace sensor