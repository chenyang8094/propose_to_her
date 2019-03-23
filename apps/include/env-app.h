#ifndef PROPOSE_ENV_APP_H
#define PROPOSE_ENV_APP_H

#include "app.h"

namespace app
{
using namespace std;

class EnvApp : public App
{
public:
  EnvApp();
  virtual ~EnvApp() {}

public:
  int Install(App * container);
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