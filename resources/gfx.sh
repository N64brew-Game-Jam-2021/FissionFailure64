#!/usr/bin/env bash

font='resources/fonts/sh-pinscher/SHPinscher-Regular.otf'
font_uni='resources/fonts/unibody/Unibody8Pro-RegularSmallCaps.otf'
font_uni_b='resources/fonts/unibody/Unibody8Pro-Bold.otf'

generate() {
    convert -strip -background $1 -fill $2 -font $3 -pointsize $4 -gravity center label:"$5" $6
}

generate_action() {
    convert -strip -background "#1f2029ff" -fill "#f9d72fff" -font  "$font_uni_b" -pointsize 10 -crop 16 -gravity West label:"$1" $2
}

generate_label() {
    convert -strip -background "#665544ff" -bordercolor "#665544ff"  -border 2x  -fill "#ffffffff"  -font "$font_uni" -pointsize 8 -interline-spacing -5 -gravity Center label:"$1" $2
}

generate_text() {
    convert -strip -background "#5b607aff" -fill "#f0f1faff"  -font "$font_uni" -pointsize 12 -extent 10x10 -gravity Center label:"$1" $2
}

generate_direction() {
    convert -strip -background "#f9d72fff" -fill "#1f2029ff"  -font "$font_uni" -pointsize 7 -extent 13x10 -gravity Center label:"$1" $2
}


# scientist
convert -strip resources/gfx/sprites/scientists/dark.png -crop 16 resources/gfx/sprites/scientists/dark-%d.png
convert -strip resources/gfx/sprites/scientists/idle0.png -crop 16 resources/gfx/sprites/scientists/idle0-%d.png
convert -strip resources/gfx/sprites/scientists/stressed0.png -crop 16 resources/gfx/sprites/scientists/stressed0-%d.png
convert -strip resources/gfx/sprites/scientists/hell0.png -crop 16 resources/gfx/sprites/scientists/hell0-%d.png
convert -strip resources/gfx/sprites/scientists/idle1.png -crop 16 resources/gfx/sprites/scientists/idle1-%d.png
convert -strip resources/gfx/sprites/scientists/stressed1.png -crop 16 resources/gfx/sprites/scientists/stressed1-%d.png
convert -strip resources/gfx/sprites/scientists/hell1.png -crop 16 resources/gfx/sprites/scientists/hell1-%d.png
convert -strip resources/gfx/sprites/scientists/idle2.png -crop 16 resources/gfx/sprites/scientists/idle2-%d.png
convert -strip resources/gfx/sprites/scientists/stressed2.png -crop 16 resources/gfx/sprites/scientists/stressed2-%d.png
convert -strip resources/gfx/sprites/scientists/hell2.png -crop 16 resources/gfx/sprites/scientists/hell2-%d.png
convert -strip resources/gfx/sprites/scientists/idle3.png -crop 16 resources/gfx/sprites/scientists/idle3-%d.png
convert -strip resources/gfx/sprites/scientists/stressed3.png -crop 16 resources/gfx/sprites/scientists/stressed3-%d.png
convert -strip resources/gfx/sprites/scientists/hell3.png -crop 16 resources/gfx/sprites/scientists/hell3-%d.png

# message
generate "#000000ff" "#ffff00ff" "$font" 24 'This game is best\nenjoyed using the\noriginal N64 controller' resources/gfx/sprites/ui/message.png

# labels
generate_label  'LIGHTS' resources/gfx/sprites/ui/label_lights.png
generate_label  'RADIO' resources/gfx/sprites/ui/label_radio.png
generate_label  'TURBINES' resources/gfx/sprites/ui/label_turbines.png
generate_label  'PUMPS' resources/gfx/sprites/ui/label_pumps.png
generate_label  'CONTROL RODS' resources/gfx/sprites/ui/label_control_rods.png
generate_label  'COMPASS' resources/gfx/sprites/ui/label_wind_turbines.png


# edited by hand
#generate_label  'AZ-S' resources/gfx/sprites/ui/label_az_5.png
generate_label  'PRESSURIZER' resources/gfx/sprites/ui/label_pressurizer.png
# edited by hand
#generate_label  'D\nA\nN\nG\nE\nR\n\nL\nE\nV\nE\nL' resources/gfx/sprites/ui/label_danger.png

generate_text 'a'  resources/gfx/sprites/ui/text_a.png
generate_text 'b'  resources/gfx/sprites/ui/text_b.png
generate_text 'c'  resources/gfx/sprites/ui/text_c.png
generate_text 'd'  resources/gfx/sprites/ui/text_d.png
generate_text '0'  resources/gfx/sprites/ui/text_0.png
generate_text '1'  resources/gfx/sprites/ui/text_1.png
generate_text '2'  resources/gfx/sprites/ui/text_2.png
generate_text '3'  resources/gfx/sprites/ui/text_3.png
generate_text '4'  resources/gfx/sprites/ui/text_4.png

generate_direction 'NW'  resources/gfx/sprites/ui/text_nw.png
generate_direction 'N'  resources/gfx/sprites/ui/text_n.png
generate_direction 'NE'  resources/gfx/sprites/ui/text_ne.png
generate_direction 'W'  resources/gfx/sprites/ui/text_w.png
generate_direction 'E'  resources/gfx/sprites/ui/text_e.png
generate_direction 'SW'  resources/gfx/sprites/ui/text_sw.png
generate_direction 'S'  resources/gfx/sprites/ui/text_s.png
generate_direction 'SE'  resources/gfx/sprites/ui/text_se.png
# actions
generate_action 'Set blue\nControl\nRod\nto B3' resources/gfx/sprites/actions/rod_b_b3-%d.png
generate_action 'Set red\nControl\nRod\nto B3' resources/gfx/sprites/actions/rod_r_b3-%d.png
generate_action 'Set blue\nControl\nRod\nto C2' resources/gfx/sprites/actions/rod_b_c2-%d.png
generate_action 'Set red\nControl\nRod\nto C2' resources/gfx/sprites/actions/rod_r_c2-%d.png
generate_action 'Turn\nOFF the\lights' resources/gfx/sprites/actions/power_off-%d.png
generate_action 'Turn the\lights\nback ON' resources/gfx/sprites/actions/power_on-%d.png
generate_action 'Set freq\nto\n242Hz' resources/gfx/sprites/actions/freq-242-%d.png
generate_action 'Call\nSpare\nParts\n(Phonebook\nin menu)' resources/gfx/sprites/actions/call-spare-%d.png

# tutorial
generate "#1f2029ff" "#f9d72fff" "$font" 24 'How to manage the stations' resources/gfx/sprites/ui/how_to.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 'LEFT' resources/gfx/sprites/ui/left.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 'CENTER' resources/gfx/sprites/ui/center.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 'RIGHT' resources/gfx/sprites/ui/right.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 'Use L and R to change station' resources/gfx/sprites/ui/use_l_r.png


# title screen
generate "#1f2029ff" "#f9d72fff" "$font_uni_b" 24 "Fission\nFailure\n64" resources/gfx/sprites/ui/logo.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "START" resources/gfx/sprites/ui/caps_start.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "START" resources/gfx/sprites/ui/caps_start_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "TUTORIAL" resources/gfx/sprites/ui/caps_tutorial.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "TUTORIAL" resources/gfx/sprites/ui/caps_tutorial_selected.png

# win / game over screens
generate "#1f2029ff" "#f9d72fff" "$font_uni_b" 24 "Well Done!" resources/gfx/sprites/ui/win.png
generate "#1f2029ff" "#f9d72fff" "$font_uni_b" 24 "Game Over..." resources/gfx/sprites/ui/gameover.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "CONTINUE" resources/gfx/sprites/ui/continue.png

# pause screen
generate "#1f2029ff" "#f9d72fff" "$font_uni_b" 24 "Pause" resources/gfx/sprites/ui/pause_big.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Resume" resources/gfx/sprites/ui/resume.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "Resume" resources/gfx/sprites/ui/resume_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Phonebook" resources/gfx/sprites/ui/phonebook.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "Phonebook" resources/gfx/sprites/ui/phonebook_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Options" resources/gfx/sprites/ui/options.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "Options" resources/gfx/sprites/ui/options_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Tutorial" resources/gfx/sprites/ui/tutorial.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "Tutorial" resources/gfx/sprites/ui/tutorial_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Credits" resources/gfx/sprites/ui/credits.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "Credits" resources/gfx/sprites/ui/credits_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Quit" resources/gfx/sprites/ui/quit.png
generate "#1f2029ff" "#f9d72fff" "$font" 18 "Quit" resources/gfx/sprites/ui/quit_selected.png

# options screen
generate "#1f2029ff" "#f9d72fff" "$font_uni_b" 24 "Options" resources/gfx/sprites/ui/options_big.png
generate "#1f2029ff" "#f9d72fff" "$font" 16 "< 100% >" resources/gfx/sprites/ui/100_selected.png
generate "#1f2029ff" "#f9d72fff" "$font" 16 "< 75 \% >" resources/gfx/sprites/ui/75_selected.png
generate "#1f2029ff" "#f9d72fff" "$font" 16 "< 50 \% >" resources/gfx/sprites/ui/50_selected.png
generate "#1f2029ff" "#f9d72fff" "$font" 16 "< 25 \% >" resources/gfx/sprites/ui/25_selected.png
generate "#1f2029ff" "#f9d72fff" "$font" 16 "< 0  \% >" resources/gfx/sprites/ui/0_selected.png
generate "#1f2029ff" "#F0F1FAff" "$font" 16 "< 100% >" resources/gfx/sprites/ui/100.png
generate "#1f2029ff" "#F0F1FAff" "$font" 16 "< 75 \% >" resources/gfx/sprites/ui/75.png
generate "#1f2029ff" "#F0F1FAff" "$font" 16 "< 50 \% >" resources/gfx/sprites/ui/50.png
generate "#1f2029ff" "#F0F1FAff" "$font" 16 "< 25 \% >" resources/gfx/sprites/ui/25.png
generate "#1f2029ff" "#F0F1FAff" "$font" 16 "< 0  \% >" resources/gfx/sprites/ui/0.png
generate "#1f2029ff" "#f9d72fff" "$font_uni" 16 "sfx" resources/gfx/sprites/ui/sfx.png

# credits screen
generate "#1f2029ff" "#f9d72fff" "$font_uni_b" 24 "Credits" resources/gfx/sprites/ui/credits_big.png
generate "#1f2029ff" "#f9d72fff" "$font_uni" 16 "programming" resources/gfx/sprites/ui/programming.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "Isabel Jimenez & Victor Vieux" resources/gfx/sprites/ui/isabel_victor.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "www.vrgl117.games" resources/gfx/sprites/ui/vrgl117games.png
generate "#1f2029ff" "#f9d72fff" "$font_uni" 16 "art" resources/gfx/sprites/ui/art.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "jphosho" resources/gfx/sprites/ui/jphosho.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "IG: @jphosho" resources/gfx/sprites/ui/atjphosho.png
generate "#1f2029ff" "#f9d72fff" "$font_uni" 16 "music" resources/gfx/sprites/ui/music.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "manuhoz" resources/gfx/sprites/ui/manuhoz.png
generate "#1f2029ff" "#F0F1FAff" "$font" 18 "IG/TT: @radiatorhymn" resources/gfx/sprites/ui/radiatorhymn.png

# phonebook
convert -strip -background "#F0F1FAff" -bordercolor "#F0F1FAff"  -border 2x  -fill "#1f2029ff"  -font "$font_uni" -pointsize 12 -interline-spacing -5 -gravity Center label:"phonebook\n\nCommissioner............0598-4627\nEmergency Services............911\nFuel Procurement......5294-2647\nIncident Response.....4676-4729\nNintendo...............800-255-3700\nNuclear Safety..........5733-4738\nPresident..................2982-2941\nPublic Affairs..........1029-4859\nReactor Supervisor..7268-2638\nSpare Parts...............3905-1273\nTreasury...................3648-3957" resources/gfx/sprites/phonebook.png

# studio logo
convert -strip -brightness-contrast -10 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_9.png
convert -strip -brightness-contrast -20 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_8.png
convert -strip -brightness-contrast -30 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_7.png
convert -strip -brightness-contrast -40 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_6.png
convert -strip -brightness-contrast -50 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_5.png
convert -strip -brightness-contrast -60 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_4.png
convert -strip -brightness-contrast -70 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_3.png
convert -strip -brightness-contrast -80 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_2.png
convert -strip -brightness-contrast -90 resources/gfx/sprites/intro/vrgl117_logo.png resources/gfx/sprites/intro/vrgl117_logo_1.png

# n64 + n64brew jam logo
convert -strip -brightness-contrast -10 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_9.png
convert -strip -brightness-contrast -20 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_8.png
convert -strip -brightness-contrast -30 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_7.png
convert -strip -brightness-contrast -40 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_6.png
convert -strip -brightness-contrast -50 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_5.png
convert -strip -brightness-contrast -60 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_4.png
convert -strip -brightness-contrast -70 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_3.png
convert -strip -brightness-contrast -80 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_2.png
convert -strip -brightness-contrast -90 resources/gfx/sprites/intro/n64brew_jam_logo.png resources/gfx/sprites/intro/n64brew_jam_logo_1.png
