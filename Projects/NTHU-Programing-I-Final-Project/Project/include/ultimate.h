//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_ULTIMATE_H
#define PROJECT_ULTIMATE_H

#endif //PROJECT_ULTIMATE_H

const int LVL1_THRE = 100, LVL2_THRE = 500, LVL3_THRE = 1000;
int counter;

void plane_ultimate() {
    if(key_state[ALLEGRO_KEY_Q]) time_coefficient -= 0.01;
    if(key_state[ALLEGRO_KEY_E]) time_coefficient += 0.01;
}

