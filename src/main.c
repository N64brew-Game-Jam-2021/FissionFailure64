#include <stdlib.h>

#include "actions.h"
#include "colors.h"
#include "control_panel.h"
#include "debug.h"
#include "fps.h"
#include "input.h"
#include "rdp.h"
#include "screens.h"
#include "sfx.h"

#define ENABLE_FPS 0
#define DISPLAY_SAFE_AREAS 1

#define MS500 500000
#define S1 1000000
#define MS20 20000
#define MS50 50000

#if DISPLAY_SAFE_AREAS
extern uint32_t __width;
extern uint32_t __height;
extern uint32_t colors[];
#endif

screen_t screen = title;
screen_t prev_screen; //used in credits to know where to go back to

int main()
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);
    rdp_init();
    audio_init(44100, 4);
    audio_write_silence();
    sfx_init();
    control_panel_init();
    timer_init();
    debug_init_isviewer();
    actions_init();
    colors_init();

    control_panel_init();

    srand(timer_ticks() & 0x7FFFFFFF);

#if ENABLE_FPS
    new_timer(TIMER_TICKS(S1), TF_CONTINUOUS, fps_timer);
#endif

    // blinking "press start" and scientist position
    new_timer(TIMER_TICKS(MS20), TF_CONTINUOUS, screen_timer);

    // improve controller detection
    new_timer(TIMER_TICKS(MS50), TF_CONTINUOUS, input_timer);

    timer_link_t *game_timer = NULL;
    display_context_t disp = 0;

    if (screen == message)
        screen_message_load();
    else if (screen == title)
        screen_title_load();

    while (true)
    {
        // get controllers
        input_t input = input_get();

        // wait for display
        while (!(disp = display_lock()))
            ;

        switch (screen)
        {
        case intro: // n64, n64brew jam and vrgl117 logo.
            if (screen_intro(disp))
            {
                screen_message_load();
                screen = message;
            }
            //screen = vru;
            break;
        //case vru:
        //    if (screen_vru(disp, &input))
        //        screen = message;
        //    break;
        case message:
            if (screen_message_draw(disp))
            {
                screen_message_unload();
                screen_title_load();
                screen = title;
                sfx_play(CH_MUSIC, SFX_THEME, true);
            }
            break;
        case title:
            if (screen_title_draw(disp, &input))
            {
                screen_title_unload();
                screen = game;
                sfx_stop(CH_MUSIC);
                control_panel_reset();
                game_timer = new_timer(TIMER_TICKS(MS500), TF_CONTINUOUS, control_panel_timer);
            }
            break;
        case game: // actual game.
            if (input.start)
            {
                screen = pause;
                sfx_set_pause(true);
                sfx_stop(CH_MUSIC);
                if (game_timer != NULL)
                {
                    stop_timer(game_timer);
                    game_timer = NULL;
                }
                screen_pause(disp, &input, true);
            }
            else
            {
                screen = screen_game(disp, &input);
                if (screen != game)
                {
                    sfx_set_pause(true);
                    sfx_stop(CH_MUSIC);
                    if (game_timer != NULL)
                    {
                        stop_timer(game_timer);
                        game_timer = NULL;
                    }
                }
            }
            break;

        case pause: // pause menu.
            switch (screen_pause(disp, &input, false))
            {
            case pause_options:
                prev_screen = pause;
                screen = options;
                break;
            case pause_resume:
                game_timer = new_timer(TIMER_TICKS(MS500), TF_CONTINUOUS, control_panel_timer);
                screen = game;
                sfx_set_pause(false);
                break;
            case pause_credits:
                prev_screen = pause;
                screen = credits;
                break;
            case pause_quit:
                actions_reset();
                control_panel_reset();
                screen_title_load();
                screen = title;
                sfx_reset();
                sfx_play(CH_MUSIC, SFX_THEME, true);
                break;
            default:
                break;
            }
            break;
        case options:
            if (screen_options(disp, &input))
                screen = prev_screen;
            break;
        case credits:
            if (screen_credits(disp, &input))
            {
                if (prev_screen == win)
                {
                    actions_reset();
                    control_panel_reset();
                    screen_title_load();
                    screen = title;
                    sfx_reset();
                    sfx_play(CH_MUSIC, SFX_THEME, true);
                }
                else
                    screen = prev_screen;
            }
            break;
        case game_over:
            if (screen_game_over(disp, &input))
            {
                actions_reset();
                control_panel_reset();
                screen_title_load();
                screen = title;
                sfx_reset();
                sfx_play(CH_MUSIC, SFX_THEME, true);
            }
            break;
        case win:
            if (screen_win(disp, &input))
            {
                prev_screen = win;
                screen = credits;
            }
            break;
        }

#if ENABLE_FPS
        // increment fps counter
        fps_frame();

        // display fps
        fps_draw(disp);
#endif

#if DISPLAY_SAFE_AREAS
        if (input.L && input.R)
        {
            graphics_draw_box(disp, 0, 0, __width, 8, colors[COLOR_RED]);            // top
            graphics_draw_box(disp, 0, __height - 8, __width, 8, colors[COLOR_RED]); // bottom

            graphics_draw_box(disp, 0, 8, __width, 8, colors[COLOR_YELLOW]);                 // top
            graphics_draw_box(disp, 0, __height - 13, __width, 5, colors[COLOR_YELLOW]);     // bottom
            graphics_draw_box(disp, 0, 8, 8, __height - 16, colors[COLOR_YELLOW]);           // left
            graphics_draw_box(disp, __width - 8, 8, 8, __height - 16, colors[COLOR_YELLOW]); // right

            // graphics_draw_box(disp, 8, 16, __width - 16, 8, colors[COLOR_BROWN]);             // top
            // graphics_draw_box(disp, 8, __height - 24, __width - 16, 11, colors[COLOR_BROWN]); // bottom
            // graphics_draw_box(disp, 8, 16, 8, __height - 32, colors[COLOR_BROWN]);            // left
            // graphics_draw_box(disp, __width - 16, 16, 8, __height - 32, colors[COLOR_BROWN]); // right
        }
#endif
        // update display
        display_show(disp);

        // Check whether one audio buffer is ready, otherwise wait for next frame to perform mixing.
        sfx_update();
    }

    return 0;
}
