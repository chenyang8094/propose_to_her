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
#include <assert.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "led-matrix.h"
#include "graphics.h"

namespace app
{

using namespace rgb_matrix;
using namespace std;

class App
{
  public:
    
    virtual ~App() {}

    /* life cycle */
    virtual int Install(App * container) = 0;
    virtual int Init(RGBMatrix *matrix) = 0;
    virtual int Start() = 0;
    virtual int Stop() = 0;
    virtual int Suspended() = 0;

    /* info */
    virtual string name() = 0;
    virtual string describe() = 0;

  protected:
    RGBMatrix *_matrix;
    volatile atomic<bool> _interrupt_received;
};

} // namespace app

#endif