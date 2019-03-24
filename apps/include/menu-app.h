#ifndef PROPOSE_MENU_APP_H
#define PROPOSE_MENU_APP_H

#include "app.h"

namespace app
{
using namespace std;

class MenuApp : public App
{
private:
  MenuApp();
  virtual ~MenuApp() {}

public:
  static App * getMenuAppSingleton();

public:
  int Install(App * container);
  int Uninstall(App * container);
  int Init(RGBMatrix *matrix);
  int Start();
  int Stop();
  int Suspended();
  int ReceiveEvent(AppEvent * event);
  AppEvent * Notification();
  string name();
  string describe();

private:
   App * _current_app;
   vector<App *> _apps;
};

} // namespace app

#endif