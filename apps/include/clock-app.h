#ifndef PROPOSE_CLOCK_APP_H
#define PROPOSE_CLOCK_APP_H

#include "app.h"

namespace app
{
using namespace std;

class ClockApp : public App
{
public:
  ClockApp();
  virtual ~ClockApp() {}

public:
  int Init(RGBMatrix *matrix);
  int Start();
  int Stop();
  int Suspended();
  string name();
  string describe();

private:
};

} // namespace app

#endif