//
// Created by root on 2021/1/15.
//
#include <allegro5/allegro_primitives.h>

#ifndef PROJECT_ULTIMATE_H
#define PROJECT_ULTIMATE_H

#endif //PROJECT_ULTIMATE_H

const int LVL1_THRE = 1, LVL2_THRE = 50, LVL3_THRE = 100;
const int ultimate_duration = 1000;
int ultimate_counter, run_ultimate_counter;

void plane_ultimate() {
    if(key_state[ALLEGRO_KEY_ENTER]) ultimate_counter += 1;
    else {
        if(ultimate_counter >= LVL3_THRE) {
            run_ultimate_counter = 1;
            ult_r = 0;
            draw_ult = false;
        } else {
            time_coefficient = 1;
        }
        ultimate_counter = 0;
    }
    if(run_ultimate_counter > 0) {
        time_coefficient = 0;
        draw_ult = true;
        ult_r += 3;
        if(ult_r >= SCREEN_W) draw_ult = false;
        run_ultimate_counter += 1;
    }
    if(run_ultimate_counter > ultimate_duration) {
        run_ultimate_counter = 0;
        time_coefficient = 1;
    }

    if(ultimate_counter >= LVL2_THRE) {
        time_coefficient = 0.1;
    }
    if(ultimate_counter >= LVL1_THRE) {
        plane.x += random_uniform(-10, 10);
        plane.y += random_uniform(-10, 10);
    }
}

