//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_SCORING_H
#define PROJECT_SCORING_H

#endif //PROJECT_SCORING_H


void score_board() {
    al_draw_textf(font_pirulen_32, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT , "HIGH: %d", history_high_score);
    al_draw_textf(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT , "SCORE: %d", score);
    al_draw_textf(font_pirulen_32, al_map_rgb(255, 255, 255), SCREEN_W, SCREEN_H - 32, ALLEGRO_ALIGN_RIGHT , "REMAINING LIVES: %d", plane.health);
}