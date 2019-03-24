#ifndef PROPOSE_IMAGE_APP_H
#define PROPOSE_IMAGE_APP_H

#include "app.h"

namespace app
{
using namespace std;

class ImageApp : public App
{
private:
  ImageApp();
  virtual ~ImageApp() {}

public:
  static ImageApp *getImageAppSingleton();

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