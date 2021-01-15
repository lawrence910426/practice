//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_BOSS_H
#define PROJECT_BOSS_H

#endif //PROJECT_BOSS_H


void spawn_boss() {
    if(score < 10) return;
    if(boss.hidden == false) return;
    allow_spawn_enemy = false;
    boss.hidden = false;
    boss.health = 30;
    boss.x = SCREEN_W / 2;
    boss.y = 0;
    boss.img = al_load_bitmap("uncle_roger.jpeg");
    boss.h = al_get_bitmap_height(boss.img);
    boss.w = al_get_bitmap_width(boss.img);
}

void move_boss() {
    if(runned_move_boss_interval++ % move_boss_interval != 0) return;
    boss.vx = rand() % 11 - 11 / 2;
    boss.vy = rand() % 11 - 11 / 2;
}

void boss_shoot_bullet() {
    if(runned_boss_shoot_bullet++ % move_boss_shoot_bullet != 0) return;
    if(boss.hidden) return;
    int amount = 10;
    int i;
    for(i = 0;i < MAX_BOSS_BULLETS;i++) {
        if(boss_bullets[i].hidden) {
            boss_bullets[i].hidden = false;
            while(0 == (boss_bullets[i].vx = random_uniform(-5, 5))) ;
            while(0 == (boss_bullets[i].vy = random_uniform(-5, 5))) ;

            boss_bullets[i].x = boss.x;
            boss_bullets[i].y = boss.y;
            boss_bullets[i].img = al_load_bitmap("msg.png");
            boss_bullets[i].w = al_get_bitmap_width(boss_bullets[i].img);
            boss_bullets[i].h = al_get_bitmap_height(boss_bullets[i].img);
            if(--amount == 0) return;
        }
    }
}
