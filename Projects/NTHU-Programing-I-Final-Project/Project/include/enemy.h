//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_ENEMY_H
#define PROJECT_ENEMY_H

#endif //PROJECT_ENEMY_H

void enemy_trajectory() {
    if(enemy_trajectory_runned_frames++ % enemy_trajectory_update_interval != 0) return;
    int i;
    for(i = 0;i < MAX_ENEMY;i++) {
        enemies[i].vx = sin(enemy_trajectory_runned_frames + i);
        enemies[i].vy = 1;
    }
}

void spawn_enemy() {
    if(spawn_enemy_runned_frames++ != spawn_enemy_interval) return;
    if(!allow_spawn_enemy) return;
    spawn_enemy_runned_frames = 0;
    int i;
    for(i = 0;i < MAX_ENEMY;i++) {
        if(enemies[i].hidden) {
            enemies[i].hidden = false;
            enemies[i].x = rand() % SCREEN_W;
            enemies[i].y = 0;
            enemies[i].health = 3;
            break;
        }
    }
    return;
}

void enemy_shoot_bullet();
const int attack_interval = 30;
int attack_frames = 0;
void enemy_attack() {
    if(attack_frames++ % attack_interval != 0) return;
    int i;
    for(i = 0;i < MAX_ENEMY;i++) {
        if(!enemies[i].hidden) {
            enemy_shoot_bullet(i);
            break;
        }
    }
}

void enemy_shoot_bullet(int enemy_id) {
    int i;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) {
        if(enemy_bullet[i].hidden) {
            enemy_bullet[i].hidden = false;
            enemy_bullet[i].img = al_load_bitmap("f-word.png");
            enemy_bullet[i].x = enemies[enemy_id].x;
            enemy_bullet[i].y = enemies[enemy_id].y;
            break;
        }
    }
}