#include <sstream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>  

#include "led-matrix.h"
#include "graphics.h"
#include "apps/include/clock-app.h"

using namespace std;
using namespace rgb_matrix;
using namespace app;

volatile bool exit_flag = false;
vector<App *> apps;
App *current_app = NULL;

static void InterruptHandler(int signo)
{
    exit_flag = true;
    current_app->Stop();
}

int main(int argc, char **argv)
{
    wiringPiSetup();

    RGBMatrix::Options matrix_options;
    matrix_options.hardware_mapping = "propose-to-her";
    matrix_options.rows = 64;
    matrix_options.cols = 64;
    // matrix_options.chain_length=1;
    // matrix_options.parallel=1;
    // matrix_options.pwm_bits=11;
    // matrix_options.pwm_lsb_nanoseconds=200;
    // matrix_options.pwm_dither_bits
    matrix_options.brightness = 80;
    // matrix_options.scan_mode=0;
    // matrix_options.row_address_type=0;
    // matrix_options.multiplexing=0;
    // matrix_options.disable_hardware_pulsing=false;
    // matrix_options.show_refresh_rate=true;
    // matrix_options.inverse_colors=false;
    // matrix_options.led_rgb_sequence="";
    // matrix_options.pixel_mapper_config="";

    rgb_matrix::RuntimeOptions runtime_opt;
    // runtime_opt.gpio_slowdown=0;
    // runtime_opt.daemon=0;
    runtime_opt.drop_privileges=0;
    // runtime_opt.do_gpio_init=false;

    RGBMatrix *matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                            runtime_opt);
    if (matrix == NULL)
        return 1;


    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    App *clock_app = new ClockApp();
    clock_app->Init(matrix);
    apps.push_back(clock_app);
    current_app = clock_app;

    
    while (!exit_flag)
    {
        current_app->Start();
    }

    for (App *app : apps)
    {
        delete app;
    }
    delete matrix;
}
