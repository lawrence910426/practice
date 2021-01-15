//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_PLANE_H
#define PROJECT_PLANE_H

#endif //PROJECT_PLANE_H



void plane_bullet_effects() {
    int i, j;
    for(i = 0;i < MAX_ENEMY;i++){
        if(!enemies[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = enemies[i].x;x <= enemies[i].x + enemies[i].w;x++)
                for(y = enemies[i].y;y <= enemies[i].y + enemies[i].h;y++)
                    for(j = 0;j < MAX_BULLET;j++) {
                        collision |= pnt_in_rect(x, y, bullets[j].x, bullets[j].y, bullets[j].w, bullets[j].h) && !bullets[j].hidden;
                        if(pnt_in_rect(x, y, bullets[j].x, bullets[j].y, bullets[j].w, bullets[j].h) && !bullets[j].hidden)
                            bullets[j].hidden = true;
                    }

            if(collision) enemies[i].health -= 1;
            if(enemies[i].health < 0) {
                enemies[i].hidden = true;
                score += 5;
            }
        }
    }

    if(!boss.hidden) {
        bool collision = false;
        int x, y;
        for(x = boss.x;x <= boss.x + boss.w;x++)
            for(y = boss.y;y <= boss.y + boss.h;y++)
                for(j = 0;j < MAX_BULLET;j++) {
                    collision |= pnt_in_rect(x, y, bullets[j].x, bullets[j].y, bullets[j].w, bullets[j].h) && !boss.hidden && !bullets[j].hidden;
                    if(pnt_in_rect(x, y, bullets[j].x, bullets[j].y, bullets[j].w, bullets[j].h) && !boss.hidden && !bullets[j].hidden)
                        bullets[j].hidden = true;
                }

        if(collision) {
            boss.health -= 1;
            score += 1;
        }
        if(boss.health < 0) {
            enemies[i].hidden = true;
            write_score(max(score, history_high_score));
            game_change_scene(SCENE_WIN);
        }
    }
}

void plane_under_attack() {
    if(--plane.health == 0) {
        write_score(max(score, history_high_score));
        game_change_scene(SCENE_MENU);
    } else {
        plane.x = SCREEN_W / 2;
        plane.y = SCREEN_H;
    }
}

void kill_plane() {
    int i;
    for(i = 0;i < MAX_ENEMY;i++){
        if(!enemies[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = enemies[i].x;x <= enemies[i].x + enemies[i].w;x++)
                for(y = enemies[i].y;y <= enemies[i].y + enemies[i].h;y++)
                    collision |= pnt_in_rect(x, y, plane.x, plane.y, plane.w, plane.h);
            if(collision) {
                enemies[i].hidden = true;
                plane_under_attack();
            }
        }
    }

    for(i = 0;i < MAX_ENEMY_BULLET;i++){
        if(!enemy_bullet[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = enemy_bullet[i].x;x <= enemy_bullet[i].x + enemy_bullet[i].w;x++)
                for(y = enemy_bullet[i].y;y <= enemy_bullet[i].y + enemy_bullet[i].h;y++)
                    collision |= pnt_in_rect(x, y, plane.x, plane.y, plane.w, plane.h);
            if(collision) {
                enemy_bullet[i].hidden = true;
                plane_under_attack();
            }
        }
    }

    for(i = 0;i < MAX_BOSS_BULLETS;i++){
        if(!boss_bullets[i].hidden) {
            bool collision = false;
            int x, y;
            for(x = boss_bullets[i].x;x <= boss_bullets[i].x + boss_bullets[i].w;x++)
                for(y = boss_bullets[i].y;y <= boss_bullets[i].y + boss_bullets[i].h;y++)
                    collision |= pnt_in_rect(x, y, plane.x, plane.y, plane.w, plane.h);
            if(collision) {
                boss_bullets[i].hidden = true;
                plane_under_attack();
            }
        }
    }

    bool boss_attacked = false;
    if(!boss.hidden) {
        bool collision = false;
        int x, y;
        for(x = boss.x;x <= boss.x + boss.w;x++)
            for(y = boss.y;y <= boss.y + boss.h;y++)
                collision |= pnt_in_rect(x, y, plane.x, plane.y, plane.w, plane.h);
        if(collision && !boss_attacked) {
            plane_under_attack();
            boss_attacked = true;
        }
    }
}

void plane_move() {
    plane.vx = plane.vy = 0;
    if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
        plane.vy -= 1;
    if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
        plane.vy += 1;
    if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
        plane.vx -= 1;
    if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
        plane.vx += 1;
    // 0.71 is (1/sqrt(2)).
    plane.y += plane.vy * 10 * (plane.vx ? 0.71f : 1);
    plane.x += plane.vx * 10 * (plane.vy ? 0.71f : 1);
    // [HACKATHON 1-1]
    // TODO: Limit the plane's collision box inside the frame.
    //       (x, y axes can be separated.)
    // Uncomment and fill in the code below.
    if (plane.x - plane.w / 2 < 0)
        plane.x = plane.w / 2;
    else if (plane.x + plane.w / 2 > SCREEN_W)
        plane.x = SCREEN_W - plane.w / 2;
    if (plane.y - plane.h / 2 < 0)
        plane.y = plane.h / 2;
    else if (plane.y + plane.h / 2 > SCREEN_H)
        plane.y = SCREEN_H - plane.h / 2;
}

void plane_attack() {
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    double now = al_get_time();
    if ((key_state[ALLEGRO_KEY_SPACE] || (state.buttons & 1)) && now - last_shoot_timestamp >= MAX_COOLDOWN) {
        int i;
        for (i = 0; i < MAX_BULLET; i++) {
            if (bullets[i].hidden) {
                last_shoot_timestamp = now;
                bullets[i].hidden = false;
                bullets[i].x = plane.x;
                bullets[i].y = plane.y;
                break;
            }
        }
    }
}