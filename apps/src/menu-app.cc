#include "menu-app.h"
#include "clock-app.h"
#include "env-app.h"

namespace app
{
using namespace rgb_matrix;

#define KEY_OK 25
#define KEY_UP 28
#define KEY_DOWN 29

void keyInterrupt(void)
{
    delay(10);
    if (0 == digitalRead(KEY_OK))
    {
        printf("KEY_OK\n");
    }
    else if (0 == digitalRead(KEY_UP))
    {
        printf("KEY_UP\n");
    }
    else if (0 == digitalRead(KEY_DOWN))
    {
        printf("KEY_DOWN\n");
    }
}

MenuApp::MenuApp() : _current_app(NULL)
{
    _apps.clear();
}

int EnvApp::Install(App *app)
{
    assert(app != NULL);
    _apps.push_back(app);
}

int MenuApp::Init(RGBMatrix *matrix)
{
    assert(matrix == NULL);
    if (-1 == wiringPiSetup())
    {
        printf("wiring init error\n");
        return -1;
    }

    wiringPiISR(KEY_OK, INT_EDGE_FALLING, &keyInterrupt);
    wiringPiISR(KEY_UP, INT_EDGE_FALLING, &keyInterrupt);
    wiringPiISR(KEY_DOWN, INT_EDGE_FALLING, &keyInterrupt);

    RGBMatrix::Options matrix_options;
    matrix_options.hardware_mapping = "propose-to-her";
    matrix_options.rows = 64;
    matrix_options.cols = 64;
    // matrix_options.chain_length=1;
    // matrix_options.parallel=1;
    // matrix_options.pwm_bits=11;
    matrix_options.pwm_lsb_nanoseconds = 200;
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
    runtime_opt.drop_privileges = 0;
    // runtime_opt.do_gpio_init=false;

    RGBMatrix *matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                            runtime_opt);
    if (matrix == NULL)
        return 1;

    this->_matrix = matrix;

    App *clock_app = new ClockApp();
    clock_app->Init(matrix);
    clock_app->Install(this);

    App *env_app = new EnvApp();
    env_app->Init(matrix);
    env_app->Install(this);

    return 0;
}

int MenuApp::Start()
{
}

int MenuApp::Stop()
{
}

int MenuApp::Suspended()
{
}

string MenuApp::name()
{
    return "MENU";
}

string MenuApp::describe()
{
    return "MENU";
}

} // namespace app