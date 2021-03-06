#ifndef PROPOSE_CLOCK_APP_H
#define PROPOSE_CLOCK_APP_H

#include "app.h"

namespace app
{
using namespace std;

class ClockApp : public App
{
private:
  ClockApp();
  virtual ~ClockApp() {}

public:
  static App *getClocAppSingleton();

public:
  int Install(App *container);
  int Uninstall(App *container);
  int Init(RGBMatrix *matrix);
  int Start();
  int Stop();
  int Suspended();
  int ReceiveEvent(AppEvent *event);
  AppEvent *Notification();
  string name();
  string describe();
};

} // namespace app

#endif