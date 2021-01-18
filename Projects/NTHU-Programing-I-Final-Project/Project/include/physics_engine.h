//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_PHYSICS_ENGINE_H
#define PROJECT_PHYSICS_ENGINE_H

#endif //PROJECT_PHYSICS_ENGINE_H

void physics_engine() {
    // [HACKATHON 2-7]
    // TODO: Update bullet coordinates.
    // 1) For each bullets, if it's not hidden, update x, y
    // according to vx, vy.
    // 2) If the bullet is out of the screen, hide it.
    // Uncomment and fill in the code below.
    int i;
    for (i = 0;i < MAX_BULLET;i++) {
        if (bullets[i].hidden)
            continue;
        bullets[i].y += bullets[i].vy;
        bullets[i].x += bullets[i].vx;
        if (bullets[i].y < 0)
            bullets[i].hidden = true;
    }

    for (i = 0;i < MAX_ENEMY;i++) {
        if (enemies[i].hidden)
            continue;
        enemies[i].y += enemies[i].vy * time_coefficient;
        enemies[i].x += enemies[i].vx * time_coefficient;
        if(enemies[i].y > SCREEN_W)
            enemies[i].hidden = true;
        //enemies[i].y = max(0, min(SCREEN_H, enemies[i].y));
        enemies[i].x = max(0, min(SCREEN_W, enemies[i].x));
    }

    const float enemy_bullet_speed = 1;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) {
        if (enemy_bullet[i].hidden)
            continue;
        int x = plane.x - enemy_bullet[i].x, y = plane.y - enemy_bullet[i].y;
        enemy_bullet[i].vx = (float)x / sqrt(x * x + y * y) * enemy_bullet_speed;
        enemy_bullet[i].vy = (float)y / sqrt(x * x + y * y) * enemy_bullet_speed + 2;
        enemy_bullet[i].y += enemy_bullet[i].vy * time_coefficient;
        enemy_bullet[i].x += enemy_bullet[i].vx * time_coefficient;
        if (bullets[i].y > SCREEN_W)
            bullets[i].hidden = true;
    }

    if(!boss.hidden) {
        boss.x += boss.vx * time_coefficient;
        boss.y += boss.vy * time_coefficient;
        boss.x = min(SCREEN_W, max(0, boss.x));
        boss.y = min(SCREEN_H - 300, max(0, boss.y));
    }

    for(i = 0;i < MAX_BOSS_BULLETS;i++) {
        if (boss_bullets[i].hidden)
            continue;
        boss_bullets[i].y += boss_bullets[i].vy * time_coefficient;
        boss_bullets[i].x += boss_bullets[i].vx * time_coefficient;
        if (boss_bullets[i].y > SCREEN_H || boss_bullets[i].y < 0 || boss_bullets[i].x < 0 || boss_bullets[i].x > SCREEN_W)
            boss_bullets[i].hidden = true;
    }
}