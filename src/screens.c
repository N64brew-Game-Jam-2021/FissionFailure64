#include "screens.h"

#include <stdlib.h>

#include "colors.h"
#include "control_panel.h"
#include "dfs.h"
#include "rdp.h"

extern uint32_t __width;
extern uint32_t __height;
extern uint32_t colors[];

static volatile uint16_t xx = 0;
static volatile bool direction = true;
static volatile uint32_t ticks = 0;

// credits screen
bool screen_credits(display_context_t disp, input_t *input)
{
    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();

    sprite_t *credits_sp = dfs_load_sprite("/gfx/sprites/ui/credits_big.sprite");
    graphics_draw_sprite(disp, __width / 2 - credits_sp->width / 2, 10, credits_sp);
    free(credits_sp);

    sprite_t *programming_sp = dfs_load_sprite("/gfx/sprites/ui/programming.sprite");
    graphics_draw_sprite(disp, __width / 2 - programming_sp->width / 2, 70, programming_sp);
    free(programming_sp);
    sprite_t *isabel_victor_sp = dfs_load_sprite("/gfx/sprites/ui/isabel_victor.sprite");
    graphics_draw_sprite(disp, __width / 2 - isabel_victor_sp->width / 2, 100, isabel_victor_sp);
    free(isabel_victor_sp);
    sprite_t *vrgl117games_sp = dfs_load_sprite("/gfx/sprites/ui/vrgl117games.sprite");
    graphics_draw_sprite(disp, __width / 2 - vrgl117games_sp->width / 2, 124, vrgl117games_sp);
    free(vrgl117games_sp);

    sprite_t *art_sp = dfs_load_sprite("/gfx/sprites/ui/art.sprite");
    graphics_draw_sprite(disp, 60 - art_sp->width / 2, 150, art_sp);
    free(art_sp);
    sprite_t *jphosho_sp = dfs_load_sprite("/gfx/sprites/ui/jphosho.sprite");
    graphics_draw_sprite(disp, 60 - jphosho_sp->width / 2, 180, jphosho_sp);
    free(jphosho_sp);
    sprite_t *atjphosho_sp = dfs_load_sprite("/gfx/sprites/ui/atjphosho.sprite");
    graphics_draw_sprite(disp, 60 - atjphosho_sp->width / 2, 204, atjphosho_sp);
    free(atjphosho_sp);

    sprite_t *music_sp = dfs_load_sprite("/gfx/sprites/ui/music.sprite");
    graphics_draw_sprite(disp, __width - 80 - music_sp->width / 2, 150, music_sp);
    free(music_sp);
    sprite_t *manuhoz_sp = dfs_load_sprite("/gfx/sprites/ui/manuhoz.sprite");
    graphics_draw_sprite(disp, __width - 80 - manuhoz_sp->width / 2, 180, manuhoz_sp);
    free(manuhoz_sp);
    sprite_t *radiatorhymn_sp = dfs_load_sprite("/gfx/sprites/ui/radiatorhymn.sprite");
    graphics_draw_sprite(disp, __width - 80 - radiatorhymn_sp->width / 2, 204, radiatorhymn_sp);
    free(radiatorhymn_sp);

    return (input->A || input->start);
}

// display the n64 logo and then the vrgl117 games logo.
// return true when the animation is done.
bool screen_intro(display_context_t disp)
{
    static int anim = 0;

    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();
    sprite_t *intro = NULL;

    switch (anim)
    {
    case 1 ... 9:
        intro = dfs_load_spritef("/gfx/sprites/intro/n64brew_jam_logo_%d.sprite", anim);
        break;
    case 10 ... 30:
        intro = dfs_load_sprite("/gfx/sprites/intro/n64brew_jam_logo.sprite");
        break;
    case 31 ... 40:
        intro = dfs_load_spritef("/gfx/sprites/intro/n64brew_jam_logo_%d.sprite", 40 - anim);
        break;
    case 41 ... 49:
        intro = dfs_load_spritef("/gfx/sprites/intro/vrgl117_logo_%d.sprite", anim - 40);
        break;
    case 50 ... 70:
        intro = dfs_load_sprite("/gfx/sprites/intro/vrgl117_logo.sprite");
        break;
    case 71 ... 79:
        intro = dfs_load_spritef("/gfx/sprites/intro/vrgl117_logo_%d.sprite", 80 - anim);
        break;
    }

    if (intro != NULL)
    {
        graphics_draw_sprite(disp, __width / 2 - intro->width / 2, __height / 2 - intro->height / 2, intro);
        free(intro);
    }

    anim++;
    return (anim >= 82);
}

// main screen for the game
screen_t screen_game(display_context_t disp, input_t *input)
{

    control_panel_input(input);

    switch (control_panel_check_status(actions_get_current()))
    {
    case DEAD:
        return game_over;

    case CORRECT:
        if (actions_next())
            return win;
        break;
    case INCORRECT:
        break;
    }

    rdp_attach(disp);

    rdp_draw_filled_rectangle_size(0, 0, 210, 180, colors[COLOR_BG]);

    sprite_t *bg = dfs_load_sprite("/gfx/sprites/bg/window.sprite");
    graphics_draw_sprite(disp, 45, 20, bg);
    free(bg);

    rdp_draw_filled_rectangle_size(0, 120, 210, 2, colors[COLOR_BLACK]);

    sprite_t *scientist = dfs_load_sprite((direction ? "/gfx/sprites/scientist/right.sprite" : "/gfx/sprites/scientist/left.sprite"));
    graphics_draw_sprite_trans(disp, xx, 100, scientist);
    free(scientist);

    control_panel_draw(disp);

    rdp_detach_display();
    return game;
}

// game over screen
bool screen_game_over(display_context_t disp, input_t *input)
{
    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();

    sprite_t *gameover_sp = dfs_load_sprite("/gfx/sprites/ui/gameover.sprite");
    graphics_draw_sprite(disp, __width / 2 - gameover_sp->width / 2, 40, gameover_sp);
    free(gameover_sp);

    sprite_t *continue_sp = dfs_load_sprite("/gfx/sprites/ui/continue.sprite");
    graphics_draw_sprite(disp, __width / 2 - continue_sp->width / 2, 200, continue_sp);
    free(continue_sp);

    return (input->A || input->start);
}

static sprite_t *message_sp = NULL;
void screen_message_load()
{
    message_sp = dfs_load_sprite("/gfx/sprites/ui/message.sprite");
}
void screen_message_unload()
{
    free(message_sp);
}

bool screen_message_draw(display_context_t disp)
{
    static int anim = 0;

    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();

    graphics_draw_sprite(disp, __width / 2 - message_sp->width / 2, 60, message_sp);

    anim++;
    return (anim >= 82);
}

// pause menu
pause_selection_t screen_pause(display_context_t disp, input_t *input, bool reset)
{
    static uint8_t selected = 0;

    if (reset)
        selected = 0;

    if (input->up)
        selected = (selected == 0 ? 3 : selected - 1);
    else if (input->down)
        selected = (selected == 3 ? 0 : selected + 1);

    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();

    sprite_t *pause_sp = dfs_load_sprite("/gfx/sprites/ui/pause_big.sprite");
    graphics_draw_sprite(disp, __width / 2 - pause_sp->width / 2, 10, pause_sp);
    free(pause_sp);

    sprite_t *resume_sp = dfs_load_sprite((selected == 0 ? "/gfx/sprites/ui/resume_selected.sprite" : "/gfx/sprites/ui/resume.sprite"));
    graphics_draw_sprite(disp, __width / 2 - resume_sp->width / 2, 90, resume_sp);
    free(resume_sp);
    sprite_t *options_sp = dfs_load_sprite((selected == 1 ? "/gfx/sprites/ui/options_selected.sprite" : "/gfx/sprites/ui/options.sprite"));
    graphics_draw_sprite(disp, __width / 2 - options_sp->width / 2, 115, options_sp);
    free(options_sp);
    sprite_t *credits_sp = dfs_load_sprite((selected == 2 ? "/gfx/sprites/ui/credits_selected.sprite" : "/gfx/sprites/ui/credits.sprite"));
    graphics_draw_sprite(disp, __width / 2 - credits_sp->width / 2, 140, credits_sp);
    free(credits_sp);
    sprite_t *quit_sp = dfs_load_sprite((selected == 3 ? "/gfx/sprites/ui/quit_selected.sprite" : "/gfx/sprites/ui/quit.sprite"));
    graphics_draw_sprite(disp, __width / 2 - quit_sp->width / 2, 165, quit_sp);
    free(quit_sp);

    if (input->A)
        return selected;
    if (input->start)
        return pause_resume;
    return pause_none;
}

static sprite_t *logo_sp = NULL;
static sprite_t *press_start_sp = NULL;
void screen_title_load()
{
    logo_sp = dfs_load_sprite("/gfx/sprites/ui/logo.sprite");
    press_start_sp = dfs_load_spritef("/gfx/sprites/ui/press_start.sprite", 12);
}

void screen_title_unload()
{
    free(logo_sp);
    free(press_start_sp);
}

bool screen_title_draw(display_context_t disp, input_t *input)
{
    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();

    graphics_draw_sprite(disp, __width / 2 - logo_sp->width / 2, 20, logo_sp);

    if (ticks % 40 > 19)
        graphics_draw_sprite(disp, __width / 2 - press_start_sp->width / 2, 180, press_start_sp);

    return (input->start);
}

/*
bool screen_vru(display_context_t disp, input_t *input)
{
    if (identify_accessory(3) == ACCESSORY_VRU)
    {
        uint8_t out[64];
        uint8_t in[64];

        // Initial sequence
        out[0] = 0x00;
        out[1] = 0x00;
        execute_raw_command(3, VRU_READ_STATUS, 2, 3, out, in);
        debugf("%02X%02X %02X%02X%02X\n", out[0], out[1], in[0], in[1], in[2]);
    }
    return true;
}
*/

// end game screen
bool screen_win(display_context_t disp, input_t *input)
{
    rdp_attach(disp);

    rdp_draw_filled_fullscreen(colors[COLOR_BLACK]);

    rdp_detach_display();

    sprite_t *win_sp = dfs_load_sprite("/gfx/sprites/ui/win.sprite");
    graphics_draw_sprite(disp, __width / 2 - win_sp->width / 2, 40, win_sp);
    free(win_sp);

    sprite_t *continue_sp = dfs_load_sprite("/gfx/sprites/ui/continue.sprite");
    graphics_draw_sprite(disp, __width / 2 - continue_sp->width / 2, 200, continue_sp);
    free(continue_sp);

    return (input->A || input->start);
}

void screen_timer()
{
    ticks++;

    if (direction)
        xx++;
    else
        xx--;

    if (xx > 200)
        direction = !direction;
    if (xx <= 0)
        direction = !direction;
}
