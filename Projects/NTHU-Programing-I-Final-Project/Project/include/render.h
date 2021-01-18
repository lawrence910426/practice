//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_RENDER_H
#define PROJECT_RENDER_H

#endif //PROJECT_RENDER_H


void draw_movable_object(MovableObject obj) {
    if (obj.hidden)
        return;
    al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
}

void render_main() {
    int i;
    al_draw_bitmap(start_img_background, 0, 0, 0);
    // [HACKATHON 2-9]
    // TODO: Draw all bullets in your bullet array.
    // Uncomment and fill in the code below.
    for (i = 0;i < MAX_BULLET; i++)
        if(!bullets[i].hidden)
            al_draw_bitmap(bullets[i].img, bullets[i].x, bullets[i].y, 0);

    draw_movable_object(plane);
    for (i = 0; i < MAX_ENEMY; i++)
        draw_movable_object(enemies[i]);

    for (i = 0; i < MAX_ENEMY_BULLET; i++)
        if(!enemy_bullet[i].hidden)
            draw_movable_object(enemy_bullet[i]);

    if(!boss.hidden) draw_movable_object(boss);

    for (i = 0;i < MAX_BOSS_BULLETS;i++)
        if(!boss_bullets[i].hidden)
            draw_movable_object(boss_bullets[i]);

    score_board();

    if(draw_ult) al_draw_filled_circle(ult_x, ult_y, ult_r, al_map_rgb(255, 255, 255));
}