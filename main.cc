#include <sstream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "menu-app.h"

using namespace std;
using namespace app;

volatile bool exit_flag = false;

App * menu_app;

static void InterruptHandler(int signo)
{
    exit_flag = true;
    menu_app->Stop();
}

int main(int argc, char **argv)
{
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    menu_app = new MenuApp();
    menu_app->Init(NULL);

    while (!exit_flag)
    {
        menu_app->Start();
    }
}
