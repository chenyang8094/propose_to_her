#include "clock-app.h"

namespace app
{

ClockApp::ClockApp()
{
    _interrupt_received = false;
}

int ClockApp::Init(RGBMatrix *matrix)
{
    this->_matrix = matrix;
    return 0;
}
int ClockApp::Start()
{
    char text_buffer[256];
    struct timespec next_time;
    next_time.tv_sec = time(NULL);
    next_time.tv_nsec = 0;
    struct tm tm;
    const char *time_format = "%H:%M:%S";
    Color color(255, 255, 0);
    Color bg_color(0, 0, 0);
    Color outline_color(0, 0, 0);
    bool with_outline = false;

    
    int x_orig = 0;
    int y_orig = 20;
    int letter_spacing = 0;

    const char *bdf_font_file = "./resource/fonts/8x13.bdf";
    rgb_matrix::Font font;
    if (!font.LoadFont(bdf_font_file))
    {
        fprintf(stderr, "Couldn't load font '%s'\n", bdf_font_file);
        return 1;
    }
    rgb_matrix::Font *outline_font = NULL;
    if (with_outline)
    {
        outline_font = font.CreateOutlineFont();
    }

    const int x = x_orig;
    int y = y_orig;

    FrameCanvas *offscreen = _matrix->CreateFrameCanvas();

    while (!_interrupt_received)
    {
        localtime_r(&next_time.tv_sec, &tm);
        strftime(text_buffer, sizeof(text_buffer), time_format, &tm);
        offscreen->Fill(bg_color.r, bg_color.g, bg_color.b);
        if (outline_font)
        {
            rgb_matrix::DrawText(offscreen, *outline_font,
                                 x - 1, y + font.baseline(),
                                 outline_color, NULL, text_buffer,
                                 letter_spacing - 2);
        }
        rgb_matrix::DrawText(offscreen, font, x, y + font.baseline(),
                             color, NULL, text_buffer,
                             letter_spacing);


        // Wait until we're ready to show it.
        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next_time, NULL);

        // Atomic swap with double buffer
        offscreen = _matrix->SwapOnVSync(offscreen);

        next_time.tv_sec += 1;
    }
    return 0;
}
int ClockApp::Stop()
{
    _interrupt_received = true;
    _matrix->Clear();
    return 0;
}
int ClockApp::Suspended()
{
    return 0;
}
string ClockApp::name()
{
    return "Clock";
}
string ClockApp::describe()
{
    return "Clock describe";
}

} // namespace app
