#include "actions.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "control_panel.h"
#include "dfs.h"

static action_new actions[ELEMENT_IDX];
static uint16_t points = 0;

static action_pair_t pair = {0};

// Last rod action
static int8_t color_prev = -1;
static int8_t pos_x_prev = -1;
static int8_t pos_y_prev = -1;

extern control_panel_t control_panel;

// actions for left station
static action_t *actions_new_freq()
{
    action_t *action = calloc(1, sizeof(action_t));
    uint16_t freqs[] = {200, 300, 400, 500, 150, 250, 350, 450, 100, 200, 300, 400, 50, 150, 250, 350, 225, 325, 425, 525, 175, 275, 375, 475, 125, 225, 325, 425, 75, 175, 275, 375, 250, 350, 450, 550, 200, 300, 400, 500, 150, 250, 350, 450, 100, 200, 300, 400, 275, 375, 475, 575, 225, 325, 425, 525, 175, 275, 375, 475, 125, 225, 325, 425, 195, 295, 395, 495, 145, 245, 345, 445, 95, 195, 295, 395, 45, 145, 245, 345, 220, 320, 420, 520, 170, 270, 370, 470, 120, 220, 320, 420, 70, 170, 270, 370, 245, 345, 445, 545, 195, 295, 395, 495, 145, 245, 345, 445, 95, 195, 295, 395, 270, 370, 470, 570, 220, 320, 420, 520, 170, 270, 370, 470, 120, 220, 320, 420, 190, 290, 390, 490, 140, 240, 340, 440, 90, 190, 290, 390, 40, 140, 240, 340, 215, 315, 415, 515, 165, 265, 365, 465, 115, 215, 315, 415, 65, 165, 265, 365, 240, 340, 440, 540, 190, 290, 390, 490, 140, 240, 340, 440, 90, 190, 290, 390, 265, 365, 465, 565, 215, 315, 415, 515, 165, 265, 365, 465, 115, 215, 315, 415, 185, 285, 385, 485, 135, 235, 335, 435, 85, 185, 285, 385, 35, 135, 235, 335, 210, 310, 410, 510, 160, 260, 360, 460, 110, 210, 310, 410, 60, 160, 260, 360, 235, 335, 435, 535, 185, 285, 385, 485, 135, 235, 335, 435, 85, 185, 285, 385, 260, 360, 460, 560, 210, 310, 410, 510, 160, 260, 360, 460, 110, 210, 310, 410};
    uint16_t freq = rand() % 88;

    while (freqs[freq] == control_panel.freq)
        freq = rand() % 88;

    action->element = ELEMENT_RADIO;
    action->expected[0] = freqs[freq];
    sprintf(action->buffer, "/gfx/sprites/actions/freq-%d", freqs[freq]);
    strcat(action->buffer, "-%d.sprite");

    return action;
}

static action_t *actions_new_compass()
{
    action_t *action = calloc(1, sizeof(action_t));
    char *dirs[] = {"NorthWest", "North", "NorthEast", "West", "East", "SouthWest", "South", "SouthEast"};
    uint16_t dir = rand() % 8;

    while (dir == control_panel.left.compass)
        dir = rand() % 8;

    action->element = ELEMENT_COMPASS;
    action->expected[0] = (dir < 4 ? dir + 1 : dir + 2);
    sprintf(action->buffer, "/gfx/sprites/actions/compass-%s", dirs[dir]);
    strcat(action->buffer, "-%d.sprite");

    return action;
}

// actions for center station
static action_t *actions_new_press()
{
    action_t *action = calloc(1, sizeof(action_t));
    uint16_t press[] = {1000, 2000, 3000, 4000};
    uint8_t pres = rand() % 4;

    while (pres == control_panel.pressure)
        pres = rand() % 4;

    action->element = ELEMENT_PRESSURIZER;
    action->expected[0] = 1 + pres;
    sprintf(action->buffer, "/gfx/sprites/actions/press-%d", press[pres]);
    strcat(action->buffer, "-%d.sprite");

    return action;
}

static action_t *actions_new_rod()
{
    action_t *action = calloc(1, sizeof(action_t));
    uint8_t color = (color_prev + 1) % 4;
    char *colors[] = {"red", "green", "blue", "orange"};
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char numbers[] = {'1', '2', '3', '4'};
    uint8_t pos_x = (pos_x_prev + 1) % 6;
    uint8_t pos_y = (pos_y_prev + 1) % 4;

    action->element = ELEMENT_GRID;
    action->expected[0] = 1 + color;
    color_prev = action->expected[0];
    action->expected[1] = pos_y;
    pos_y_prev = pos_y;
    action->expected[2] = pos_x;
    pos_x_prev = pos_x;
    sprintf(action->buffer, "/gfx/sprites/actions/rod_%s_%c%c", colors[color], letters[pos_x], numbers[pos_y]);
    strcat(action->buffer, "-%d.sprite");

    return action;
}

// actions for right station
static action_t *actions_new_power()
{
    action_t *action = calloc(1, sizeof(action_t));
    uint16_t powers[] = {0, 125, 250, 375, 500};
    uint8_t power = rand() % 5;

    while (power == control_panel.power)
        power = rand() % 5;

    action->element = ELEMENT_TURBINES;
    action->expected[0] = powers[power];
    sprintf(action->buffer, "/gfx/sprites/actions/power-%d", powers[power]);
    strcat(action->buffer, "-%d.sprite");

    return action;
}

static action_t *actions_new_pumps()
{
    action_t *action = calloc(1, sizeof(action_t));

    action->element = ELEMENT_PUMPS;
    action->expected[0] = 9;
    strcpy(action->buffer, "/gfx/sprites/actions/pumps-%d.sprite");

    return action;
}

static action_t *actions_new_spare_part()
{
    action_t *action = calloc(1, sizeof(action_t));

    action->element = ELEMENT_KEYPAD;
    action->expected[0] = 3;
    action->expected[1] = 9;
    action->expected[2] = 0;
    action->expected[3] = 5;
    action->expected[4] = 1;
    action->expected[5] = 2;
    action->expected[6] = 7;
    action->expected[7] = 3;
    strcpy(action->buffer, "/gfx/sprites/actions/call-spare-%d.sprite");

    return action;
}

static action_t *actions_new_az5()
{
    action_t *action = calloc(1, sizeof(action_t));
    char *dependants[] = {"turbines", "compass"};
    element_t elements[] = {ELEMENT_TURBINES, ELEMENT_COMPASS};
    uint8_t desired_values[] = {0, 2};

    uint8_t dependants_pos = rand() % 2;
    action->element = ELEMENT_AZ5;
    action->expected[0] = elements[dependants_pos];
    action->expected[1] = desired_values[dependants_pos];

    sprintf(action->buffer, "/gfx/sprites/actions/az5-%s", dependants[dependants_pos]);
    strcat(action->buffer, "-%d.sprite");

    return action;
}

void actions_init()
{
    actions[ELEMENT_TURBINES] = actions_new_power;
    actions[ELEMENT_COMPASS] = actions_new_compass;
    actions[ELEMENT_PRESSURIZER] = actions_new_press;
    actions[ELEMENT_RADIO] = actions_new_freq;
    actions[ELEMENT_GRID] = actions_new_rod;
    actions[ELEMENT_PUMPS] = actions_new_pumps;
    actions[ELEMENT_KEYPAD] = actions_new_spare_part;
    actions[ELEMENT_AZ5] = actions_new_az5;

    actions_reset();
}

uint16_t actions_get_points()
{
    return points;
}

uint8_t difficulty()
{
    if (points < EASY)
    {
        return ELEMENT_RADIO;
    }
    if (points < NORMAL)
    {
        return ELEMENT_KEYPAD;
    }

    return ELEMENT_IDX;
}

static action_t *get_action(uint8_t unwanted_action)
{
    uint8_t wanted_action = rand() % (difficulty());
    while (wanted_action == unwanted_action)
        wanted_action = rand() % (difficulty());
    return actions[wanted_action]();
}

action_pair_t actions_get_current()
{
    return pair;
}

bool actions_next()
{
    if (pair.top != 0)
    {
        dfs_free_sprites(pair.top->text);
        free(pair.top);
    }

    pair.top = get_action(255);
    if (points > EXTRA_HARD && pair.top->element != ELEMENT_AZ5)
    {
        if (pair.bottom != 0)
        {
            dfs_free_sprites(pair.bottom->text);
            free(pair.bottom);
        }
        pair.bottom = get_action(pair.top->element);
    }
    points++;
    return (points >= EXTRA_HARD * 2);
}

void actions_reset()
{
    actions_next();
    points = 0;
}
