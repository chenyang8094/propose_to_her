#ifndef PROPOSE_ENV_APP_H
#define PROPOSE_ENV_APP_H

#include "app.h"

namespace app
{
using namespace std;

class EnvApp : public App
{
private:
  EnvApp();
  virtual ~EnvApp() {}

public:
  static EnvApp *getEnvAppSingleton();

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

private:
};

} // namespace app

#endif