//
// Created by root on 2021/1/15.
//

#ifndef PROJECT_INIT_H
#define PROJECT_INIT_H

#endif //PROJECT_INIT_H

void load_main_scene_resources() {
    start_img_background = load_bitmap_resized("background.png", SCREEN_W, SCREEN_H);

    start_img_plane = al_load_bitmap("plane.png");
    if (!start_img_plane)
        game_abort("failed to load image: plane.png");

    start_img_enemy = load_bitmap_resized("gordon-ramsey.png", 70, 70);
    if (!start_img_enemy)
        game_abort("failed to load image: smallfighter0006.png");

    img_bullet = al_load_bitmap("image12.png");
    if (!img_bullet)
        game_abort("failed to load image: image12.png");
}

void main_scene_start() {
    load_main_scene_resources();

    score = 0;
    history_high_score = get_history_score();
    int i;
    plane.img = start_img_plane;
    plane.x = 400;
    plane.y = 500;
    plane.w = al_get_bitmap_width(plane.img);
    plane.h = al_get_bitmap_height(plane.img);
    plane.health = 10;

    for (i = 0; i < MAX_ENEMY; i++) {
        enemies[i].img = start_img_enemy;
        enemies[i].w = al_get_bitmap_width(start_img_enemy);
        enemies[i].h = al_get_bitmap_height(start_img_enemy);
        enemies[i].x = 30;
        enemies[i].y = i * 20;
    }
    // [HACKATHON 2-6]
    // TODO: Initialize bullets.
    // For each bullets in array, set their w and h to the size of
    // the image, and set their img to bullet image, hidden to true,
    // (vx, vy) to (0, -3).
    // Uncomment and fill in the code below.
    for (i = 0; i < MAX_BULLET; i++) {
        bullets[i].w = al_get_bitmap_width(img_bullet);
        bullets[i].h = al_get_bitmap_height(img_bullet);
        bullets[i].img = img_bullet;
        bullets[i].vx = 0;
        bullets[i].vy = -10;
        bullets[i].hidden = true;
    }

    for(i = 0;i < MAX_ENEMY;i++) enemies[i].health = 3;
    for(i = 0;i < MAX_ENEMY;i++) enemies[i].x = 30;
    for(i = 0;i < MAX_ENEMY;i++) enemies[i].y = i * 10;
    for(i = 0;i < MAX_ENEMY;i++) enemies[i].hidden = false;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) enemy_bullet[i].hidden = true;
    for(i = 0;i < MAX_ENEMY_BULLET;i++) {
        enemy_bullet[i].img = al_load_bitmap("rocket-1.png");
        enemy_bullet[i].h = al_get_bitmap_height(enemy_bullet[i].img);
        enemy_bullet[i].w = al_get_bitmap_width(enemy_bullet[i].img);
    }

    for(i = 0;i < MAX_BOSS_BULLETS;i++)
        boss_bullets[i].hidden = true;
}
