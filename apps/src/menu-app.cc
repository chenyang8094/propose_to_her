#include "menu-app.h"
#include "clock-app.h"
#include "env-app.h"
#include "image-app.h"

namespace app
{
using namespace rgb_matrix;
using namespace std;

#define KEY_OK 25
#define KEY_UP 28
#define KEY_DOWN 29

FrameCanvas *offscreen;
Color color(0, 255, 0);
Color bg_color(0, 0, 0);
rgb_matrix::Font font;

void keyInterrupt(void)
{
    delay(10);
    if (0 == digitalRead(KEY_OK))
    {
        App *mainApp = MenuApp::getMenuAppSingleton();
        AppEvent appEvent;
        appEvent.to_app = mainApp;
        appEvent.event_type = EventType::OK;
        mainApp->ReceiveEvent(&appEvent);
    }
    else if (0 == digitalRead(KEY_UP))
    {
        App *mainApp = MenuApp::getMenuAppSingleton();
        AppEvent appEvent;
        appEvent.to_app = mainApp;
        appEvent.event_type = EventType::UP;
        mainApp->ReceiveEvent(&appEvent);
    }
    else if (0 == digitalRead(KEY_DOWN))
    {
        printf("KEY_DOWN\n");
    }
}

MenuApp::MenuApp() : _current_app(NULL)
{
    _apps.clear();
    _stop = false;
    _appInfo = "Menu App";
    _appName = "Menu App";
}

App *MenuApp::getMenuAppSingleton()
{
    static MenuApp menu_app;
    return &menu_app;
}

int MenuApp::Install(App *app)
{
    assert(app != NULL);
    vector<App *>::iterator iter;
    if ((iter = find(_apps.begin(), _apps.end(), app)) != _apps.end())
        return 0;
    _apps.push_back(app);
}

int MenuApp::Uninstall(App *app)
{
    if (!app)
        return 0;

    vector<App *>::iterator iter;
    if ((iter = find(_apps.begin(), _apps.end(), app)) == _apps.end())
    {
        return 0;
    }
    else
    {
        _apps.erase(iter);
    }
}

int MenuApp::ReceiveEvent(AppEvent *event)
{
    App *oldApp;
    vector<App *>::iterator iter;
    if (event->to_app == this)
    {
        switch (event->event_type)
        {
        case EventType::OK:
            oldApp = _current_app;

            iter = find(_apps.begin(), _apps.end(), _current_app);
            if (++iter == _apps.end())
            {
                iter = _apps.begin();
            }
            _current_app = *iter;

            // _matrix->Clear();
            rgb_matrix::DrawText(offscreen, font,
                                 30, 20 + font.baseline(),
                                 color, NULL, _current_app->describe().c_str(),
                                 0);
            offscreen = _matrix->SwapOnVSync(offscreen);

            oldApp->Stop();
            break;

        default:
            break;
        }
    }
}

AppEvent *MenuApp::Notification()
{
    return NULL;
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

    matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                 runtime_opt);
    if (matrix == NULL)
        return 1;

    this->_matrix = matrix;

    App *env_app = EnvApp::getEnvAppSingleton();
    env_app->Init(matrix);
    env_app->Install(this);

    App *clock_app = ClockApp::getClocAppSingleton();
    clock_app->Init(matrix);
    clock_app->Install(this);

    App *image_app = ImageApp::getImageAppSingleton();
    image_app->Init(matrix);
    image_app->Install(this);

    if (_apps.size() > 0)
        _current_app = _apps[0];

    const char *bdf_font_file = "./resource/fonts/8x13.bdf";
    
    if (!font.LoadFont(bdf_font_file))
    {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
        return 1;
    }
    offscreen = _matrix->CreateFrameCanvas();

    offscreen->Fill(bg_color.r, bg_color.g, bg_color.b);

    rgb_matrix::DrawText(offscreen, font,
                         30, 20 + font.baseline(),
                         color, NULL, this->_appInfo.c_str(),
                         0);
    offscreen = _matrix->SwapOnVSync(offscreen);
    return 0;
}

int MenuApp::Start()
{
    while (!_stop)
    {
        _current_app->Start();
    }
}

int MenuApp::Stop()
{
    _stop = true;
    for (App *app : _apps)
    {
        app->Stop();
    }
    _matrix->Clear();
}

int MenuApp::Suspended()
{
}

string MenuApp::name()
{
    return _appName;
}

string MenuApp::describe()
{
    return _appInfo;
}

} // namespace app