#ifndef PROPOSE_BEEP_H
#define PROPOSE_BEEP_H

namespace sensor
{
#define BEEP_PIN 31

void beep_init();
void beep_on();
void beep_off();
void beep_toggle();

} // namespace sensor
#endif