//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_BULLET_COLLISION_H
#define PROJECT_BULLET_COLLISION_H

#endif //PROJECT_BULLET_COLLISION_H

void kill_bullets() {
    int i, j, x, y;
    for(i = 0;i < MAX_BULLET;i++) for(j = 0;j < MAX_ENEMY_BULLET;j++) {
            bool collision = false;
            for(x = bullets[i].x; x <= bullets[i].x + bullets[i].w; x++) for(y = bullets[i].y; y <= bullets[i].y + bullets[i].h; y++)
                    collision |= pnt_in_rect(x, y, enemy_bullet[j].x, enemy_bullet[j].y, enemy_bullet[j].w, enemy_bullet[j].h) && !bullets[i].hidden && !enemy_bullet[j].hidden;
            if(collision) {
                bullets[i].hidden = true;
                enemy_bullet[j].hidden = true;
                score += 1;
            }
        }

    for(i = 0;i < MAX_BULLET;i++) for(j = 0;j < MAX_BOSS_BULLETS;j++) {
            bool collision = false;
            for(x = bullets[i].x; x <= bullets[i].x + bullets[i].w; x++) for(y = bullets[i].y; y <= bullets[i].y + bullets[i].h; y++)
                    collision |= pnt_in_rect(x, y, boss_bullets[j].x, boss_bullets[j].y, boss_bullets[j].w, boss_bullets[j].h) && !bullets[i].hidden && !boss_bullets[j].hidden;
            if(collision) {
                bullets[i].hidden = true;
                boss_bullets[j].hidden = true;
                score += 1;
            }
        }
}