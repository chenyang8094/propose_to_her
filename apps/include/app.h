#ifndef PROPOSE_APP_H
#define PROPOSE_APP_H

#include <atomic>
#include <string>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "led-matrix.h"
#include "graphics.h"
#include "content-streamer.h"

namespace app
{

using namespace rgb_matrix;
using namespace std;

class App;
enum AppType
{
  T1,
  T2
};

enum EventType
{
  OK,
  UP,
  DOWN,
};

struct AppEvent
{
  App *to_app;
  EventType event_type;
  string message;
};

class App
{
protected:
  virtual ~App() {}

public:
  /* life cycle */
  virtual int Install(App *container) = 0;
  virtual int Uninstall(App *container) = 0;
  virtual int Init(RGBMatrix *matrix) = 0;
  virtual int Start() = 0;
  virtual int Stop() = 0;
  virtual int Suspended() = 0;

  /* event */
  virtual int ReceiveEvent(AppEvent *event) = 0;
  virtual AppEvent *Notification() = 0;

  /* info */
  virtual string name() = 0;
  virtual string describe() = 0;

protected:
  string _appName;
  string _appInfo;
  AppType _appType;
  RGBMatrix *_matrix;
  volatile atomic<bool> _stop;
};

} // namespace app

#endif