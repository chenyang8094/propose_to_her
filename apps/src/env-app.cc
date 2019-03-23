#include "env-app.h"
#include "apps/include/clock-app.h"
#include "bmp180.h"

namespace app
{

#define BMP180_ADDR 0x77
#define IIC_DEV "/dev/i2c-1"

struct bmp180_t;
bmp180_t *bmp;

EnvApp::EnvApp()
{
}

int EnvApp::Install(App * container){
   assert(container != NULL);
   container->Install(this);
}

int EnvApp::Init(RGBMatrix *matrix)
{
    this->_matrix = matrix;

    bmp = (bmp180_t *)bmp180_init(BMP180_ADDR, IIC_DEV);
    bmp180_eprom_t eprom;
    bmp180_dump_eprom(bmp, &eprom);

    return 0;
}

int EnvApp::Start()
{
    while (!_interrupt_received)
    {
        if (bmp != NULL)
        {
            int i;
            for (i = 0; i < 10; i++)
            {
                float t = bmp180_temperature(bmp);
                long p = bmp180_pressure(bmp);
                float alt = bmp180_altitude(bmp);
                printf("t = %f, p = %lu, a= %f\n", t, p, alt);
                
            }
        }
    }
}

int EnvApp::Stop()
{
    bmp180_close(bmp);
}

int EnvApp::Suspended()
{
}

string EnvApp::name()
{
    return "environment";
}

string EnvApp::describe()
{
    return "environment";
}

} // namespace app