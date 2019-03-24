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

App * main_app;

static void InterruptHandler(int signo)
{
    main_app->Stop();
}

int main(int argc, char **argv)
{
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    main_app = MenuApp::getMenuAppSingleton();
    main_app->Init(NULL);
    main_app->Start();
}
