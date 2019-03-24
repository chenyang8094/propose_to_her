#include "env-app.h"
#include "bmp180.h"
#include "beep.h"

namespace app
{

using namespace sensor;

#define BMP180_ADDR 0x77
#define IIC_DEV "/dev/i2c-1"

struct bmp180_t;
bmp180_t *bmp;

EnvApp::EnvApp()
{
    _appName = "Env App";
    _appInfo = "Env APp";
    _stop = false;
}

EnvApp *EnvApp::getEnvAppSingleton(){
    static EnvApp envApp;
    return &envApp;
}

int EnvApp::Install(App *container)
{
    assert(container != NULL);
    container->Install(this);
}

int EnvApp::Uninstall(App * container){
    assert(container != NULL);
    container->Uninstall(this);
}

int EnvApp::ReceiveEvent(AppEvent * event){

}

AppEvent * EnvApp::Notification(){
    return NULL;
}

int EnvApp::Init(RGBMatrix *matrix)
{
    this->_matrix = matrix;

    bmp = (bmp180_t *)bmp180_init(BMP180_ADDR, IIC_DEV);
    assert(bmp != NULL);
    bmp180_eprom_t eprom;
    bmp180_dump_eprom(bmp, &eprom);

    beep_init();

    return 0;
}

int EnvApp::Start()
{
    while (!_stop)
    {
        float t = bmp180_temperature(bmp);
        long p = bmp180_pressure(bmp);
        float alt = bmp180_altitude(bmp);
        printf("t = %f, p = %lu, a= %f\n", t, p, alt);
        beep_on();
        sleep(1);
        beep_off();
        sleep(1);
    }
}

int EnvApp::Stop()
{
    _stop = true;
    bmp180_close(bmp);
    _matrix->Clear();
}

int EnvApp::Suspended()
{
}

string EnvApp::name()
{
    return _appName;
}

string EnvApp::describe()
{
    return _appInfo;
}

} // namespace app